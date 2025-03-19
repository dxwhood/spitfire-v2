#include "search.h"
#include "utils/display.h"

namespace chess{

namespace search{

    void think(Board &board, int maxDepth, bool useTimeControl, int timeLimitMs, bool uci) {
        searchState.reset();
        searchState.timeLimitMs = timeLimitMs;


        Move bestMove;

        for (int depth = 1; depth <= maxDepth; ++depth) {

            if (searchState.searchStopped) {
                break;
            }

            Move currentBestMove;
            int score = negamaxAB(board, depth, NEG_INF, POS_INF, currentBestMove, useTimeControl, uci);

            // Check time limit if enabled
            if (useTimeControl) {
                if (searchState.searchStopped) {
                        if (searchState.bestScoreThisIteration > searchState.bestScore) {
                            searchState.bestScore = searchState.bestScoreThisIteration;
                            bestMove = searchState.bestMove;
                        }
                        break; 
                    }
            }

            // Store the best move found at this depth
            bestMove = currentBestMove;        
            searchState.bestMove = currentBestMove;
            searchState.bestScore = score;
            searchState.currentDepth = depth;
        
            if (uci && !searchState.searchStopped) {
                std::cout << "info depth " << depth << " score cp " << score << std::endl;
            }

        }

        // Update time left
        auto endTime = std::chrono::high_resolution_clock::now();
        int elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - searchState.startTime).count();
        searchState.timeLeft -= elapsedMs;
    }

    void think(Board &board, int depth) {
        think(board, depth, false, 0);
    }

    int negamaxAB(Board &board, int depth, int alpha, int beta, Move &bestMove, bool useTimeControl, bool uci) {
        ++searchState.nodeCount;

        const int MATE_VALUE = 100000;

        if (__builtin_expect(searchState.searchStopped, 0)) {
            return 0;
        }

        // Check every TIME_CHECK_INTERVAL nodes
        if (__builtin_expect((searchState.nodeCount % TIME_CHECK_INTERVAL == 0), 0)) {
            auto currentTime = std::chrono::high_resolution_clock::now();
            int elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - searchState.startTime).count();

            if (useTimeControl && (elapsedMs >= searchState.timeLimitMs)) {
                searchState.searchStopped = true;
                return 0;
            }

            if (uci) {
                std::cout << "info nodes " << searchState.nodeCount << std::endl;
                std::cout << "info time " << elapsedMs << std::endl;
                std::cout << "info nps " << searchState.nodeCount / (elapsedMs / 1000) << std::endl;
                if (search::stopSearch.load()) {
                    searchState.searchStopped = true;
                    return 0;
                }
            }
        }

        uint64_t hash = searchState.tt.computeHash(board);
        int ttScore;
        Move ttBestMove = Move();

        // Check if position already stored in TT
        if (searchState.tt.probe(hash, depth, alpha, beta, ttScore, ttBestMove)) {
            return ttScore;
        }

        if (depth == 0) {
            return quiescence(board, alpha, beta, useTimeControl); // Evaluate leaf node
        }

        // Check for threefold repetition
        if (board.repetitionTable[hash] >= 3) {
            return 0;
        }

        int maxScore = -MATE_VALUE;  
        Move bestFoundMove; 

        MoveList moveList = Movegen::generateValidMoves(
            board, board.getIsWhiteTurn() ? Color::WHITE : Color::BLACK
        );

        // TODO: Add tt best move to the front of the move list 
        // Add tt best move to the front of the move list
        // if (ttBestMove.isValid()) {
        //     moveList.moves[moveList.count++] = ttBestMove;
        // }

        moveOrdering(moveList, board, depth);

        if (moveList.count == 0) {  // No legal moves: checkmate or stalemate
            return Movegen::isCheck(board, board.getIsWhiteTurn() ? Color::WHITE : Color::BLACK)
                ? -MATE_VALUE + depth   // Mate: prefer faster mates (so add depth)
                : 0;  // Stalemate = draw
        }

        for (int i=0; i<moveList.count; i++) {
            
            if (!moveList.moves[i].isValid()){
                std::cout << "Invalid move: " << moveList.moves[i] << std::endl;
                continue;
            }
            board.makeMove(moveList.moves[i]);
            board.repetitionTable[searchState.tt.computeHash(board)]++;
            Move tempMove;  // Store best move for the recursive call
            int score = -negamaxAB(board, depth - 1, -beta, -alpha, tempMove, useTimeControl, uci);
            board.repetitionTable[searchState.tt.computeHash(board)]--;
            board.unmakeMove(moveList.moves[i]);

            if (std::abs(score) >= MATE_VALUE - 1000) {
                if (score > 0)
                    score -= depth;
                else
                    score += depth;
            }

            if (score > maxScore) {
                maxScore = score;
                bestFoundMove = moveList.moves[i];
                searchState.bestScoreThisIteration = maxScore;
            }
            
            if (score > alpha) {
                alpha = score;
                // History Heuristic
                if (!moveList.moves[i].isCapture()) {
                    searchState.historyHeuristic[enumToInt(moveList.moves[i].getFrom())][enumToInt(moveList.moves[i].getTo())] += depth * depth;
                }
            }
            
            if (alpha >= beta) {
                // Killer Heuristic
                if (!moveList.moves[i].isCapture()) {
                    searchState.killerMoves[depth][1] = searchState.killerMoves[depth][0];
                    searchState.killerMoves[depth][0] = moveList.moves[i];
            }
                break;  // Beta cutoff: prune this branch.
            }
        }

        // Store in TT
        TTFlag flag = (maxScore >= beta) ? LOWERBOUND : (maxScore > alpha) ? EXACT : UPPERBOUND;
        searchState.tt.store(hash, depth, maxScore, flag, bestFoundMove);

        bestMove = bestFoundMove;

        return maxScore;
    }

    int quiescence(Board &board, int alpha, int beta, bool useTimeControl) {
        if (__builtin_expect(search::searchState.searchStopped, 0)) {
            return 0;  // Stop searching if time is up
        }

        int standPat = eval::evaluate(board);

        // Beta cutoff
        if (standPat >= beta) {
            return beta;
        }

        if (standPat > alpha) {
            alpha = standPat;
        }

      
        MoveList moveList = Movegen::generateCapturesAndChecks(board, board.getIsWhiteTurn() ? Color::WHITE : Color::BLACK);

        for (int i = 0; i < moveList.count; i++) {
            board.makeMove(moveList.moves[i]);

            // Recursive quiescence search with negamax
            int score = -quiescence(board, -beta, -alpha, useTimeControl);

            board.unmakeMove(moveList.moves[i]);

            if (score >= beta) {
                return beta;  
            }

            if (score > alpha) {
                alpha = score; 
            }
        }

        return alpha;
    }


    int negamaxAB(Board &board, int depth, int alpha, int beta, Move &bestMove, int indent) {
        // Build an indentation string for pretty printing
        std::string indentStr(indent, ' ');
        
        // Determine the side to move (for printing purposes)
        std::string currentSide = board.getIsWhiteTurn() ? "white" : "black";
        
        // Base case: leaf node
        if (depth == 0) {
            int evalScore = eval::evaluate(board);
            std::cout << indentStr << "Leaf eval for " << currentSide 
                    << ": " << evalScore 
                    << " (alpha: " << alpha << ", beta: " << beta << ")\n";
            //Display::printBoard(board);
            return evalScore;
        }
        
        int maxScore = -1000000;
        Move bestFoundMove;
        
        // Generate moves for the current side.
        MoveList moveList = Movegen::generateValidMoves(
            board, board.getIsWhiteTurn() ? Color::WHITE : Color::BLACK
        );
        
        if (moveList.count == 0) {  // No legal moves: checkmate or stalemate
            int terminalScore = Movegen::isCheck(board, board.getIsWhiteTurn() ? Color::WHITE : Color::BLACK) ? -100000 : 0;
            std::cout << indentStr << "No legal moves for " << currentSide 
                    << " - returning " << terminalScore << "\n";
            return terminalScore;
        }
        
        // Print a header for this level of moves
        std::cout << indentStr << "Exploring moves for " << currentSide 
                << " at depth " << depth 
                << " (alpha: " << alpha << ", beta: " << beta << "):\n";
        
        // Loop through each move.
        for (int i=0; i<moveList.count; i++) {
            // Print the move header at this level.
            std::cout << indentStr << "  <move-" << currentSide << " " 
                    << moveList.moves[i] << ">" 
                    << " (alpha: " << alpha << ", beta: " << beta << ")\n";
            
            board.makeMove(moveList.moves[i]);
            Move tempMove;  // Temporary storage for the best move in the recursion
            int score = -negamaxAB(board, depth - 1, -beta, -alpha, tempMove, indent + 4);
            board.unmakeMove(moveList.moves[i]);
            
            // Print the score returned for this move.
            std::cout << indentStr << "  Returned score for " 
                    << moveList.moves[i] << ": " << score << "\n";
            
            // Update the best score and best move if needed.
            if (score > maxScore) {
                maxScore = score;
                bestFoundMove = moveList.moves[i];
            }
            
            // Update alpha and check for beta cutoff.
            if (score > alpha) {
                alpha = score;
            }
            if (alpha >= beta) {
                std::cout << indentStr << "  Beta cutoff reached (alpha: " << alpha 
                        << " >= beta: " << beta << ")\n";
                break;
            }
        }
        
        // Print the best score found at this level.
        std::cout << indentStr << "Best score for " << currentSide 
                << " at depth " << depth << ": " << maxScore << "\n";
        bestMove = bestFoundMove;
        return maxScore;
    }

    int negamax(Board &board, int depth, Move &bestMove) {
        if (depth == 0) {
            return eval::evaluate(board);  // Returns evaluation score at leaf node
        }

        int maxScore = -1000000;
        Move bestFoundMove; 

        MoveList moveList = Movegen::generateValidMoves(
            board, board.getIsWhiteTurn() ? Color::WHITE : Color::BLACK
        );

        if (moveList.count == 0) {  // No legal moves: checkmate or stalemate
            return Movegen::isCheck(
                board, board.getIsWhiteTurn() ? Color::WHITE : Color::BLACK
            ) ? -100000 : 0;  
        }

        for (int i=0; i<moveList.count; i++) {
            board.makeMove(moveList.moves[i]);
            Move tempMove;  // Store best move for the next depth
            int score = -negamax(board, depth - 1, tempMove); // Recursive call
            board.unmakeMove(moveList.moves[i]);

            if (score > maxScore) {
                maxScore = score;
                bestFoundMove = moveList.moves[i];  
            }
        }

        bestMove = bestFoundMove;  
        return maxScore;
    }

    int moveScore(const Move &move, const Board &board, int depth) {
        int score = 0;

        // PV move
        if (move == search::searchState.bestMove) {
            return 1000000;
        }

        // MVV-LVA
        if (move.isCapture()) {
            if (move.getMoveCode() == MoveCode::EN_PASSANT) {
                return 100000;
            } else {
            int victimValue = PIECE_VALUES_RELATIVE[enumToInt(board.getPieceType(move.getTo()).value())];
            int attackerValue = PIECE_VALUES_RELATIVE[enumToInt(board.getPieceType(move.getFrom()).value())];

            score += 100000 + (victimValue - attackerValue);  // Captures get priority
            }
        }

        // Killer Moves
        if (move == search::searchState.killerMoves[depth][0].value_or(Move())) {
            score += 9000;
        }
        if (move == search::searchState.killerMoves[depth][1].value_or(Move())) {
            score += 8000;
        }

        // History Heuristic
        score += search::searchState.historyHeuristic[enumToInt(move.getFrom())][enumToInt(move.getTo())];

        return score;
        
    }

    void moveOrdering(MoveList &moves, const Board &board, int depth) {
        std::stable_sort(moves.moves.begin(), moves.moves.begin() + moves.count, [&](const Move &a, const Move &b) {
            return moveScore(a, board, depth) > moveScore(b, board, depth);
        });
    }



}
}