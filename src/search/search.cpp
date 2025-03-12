#include "search.h"
#include "utils/display.h"

namespace chess{

namespace search{

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

    int negamaxAB(Board &board, int depth, int alpha, int beta, Move &bestMove) {
    const int MATE_VALUE = 100000;

    if (depth == 0) {
        return eval::evaluate(board);  // Evaluate leaf node
    }

    int maxScore = -MATE_VALUE;  // Start with a very low score
    Move bestFoundMove; 

    MoveList moveList = Movegen::generateValidMoves(
        board, board.getIsWhiteTurn() ? Color::WHITE : Color::BLACK
    );

    if (moveList.count == 0) {  // No legal moves: checkmate or stalemate
        // If in check, it's mate; otherwise stalemate (draw)
        return Movegen::isCheck(board, board.getIsWhiteTurn() ? Color::WHITE : Color::BLACK)
               ? -MATE_VALUE + depth   // Mate: prefer faster mates (so add depth)
               : 0;  // Stalemate = draw
    }

    for (int i=0; i<moveList.count; i++) {
        board.makeMove(moveList.moves[i]);
        Move tempMove;  // Store best move for the recursive call
        int score = -negamaxAB(board, depth - 1, -beta, -alpha, tempMove);
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
        }
        
        if (score > alpha) {
            alpha = score;
        }
        
        if (alpha >= beta) {
            break;  // Beta cutoff: prune this branch.
        }
    }

    bestMove = bestFoundMove;
    return maxScore;
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


}
}