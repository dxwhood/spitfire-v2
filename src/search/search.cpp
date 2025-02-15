#include "search.h"

namespace chess{

namespace search{

    int negamax(Board &board, int depth, Move &bestMove) {
        if (depth == 0) {
            return eval::evaluate(board);  // Returns evaluation score at leaf node
        }

        int maxScore = -1000000;
        Move bestFoundMove; 

        std::vector<Move> moves = Movegen::generateValidMoves(
            board, board.getIsWhiteTurn() ? Color::WHITE : Color::BLACK
        );

        if (moves.empty()) {  // No legal moves: checkmate or stalemate
            return Movegen::isCheck(
                board, board.getIsWhiteTurn() ? Color::WHITE : Color::BLACK
            ) ? -100000 : 0;  
        }

        for (Move move : moves) {
            board.makeMove(move);
            Move tempMove;  // Store best move for the next depth
            int score = -negamax(board, depth - 1, tempMove); // Recursive call
            board.unmakeMove(move);

            if (score > maxScore) {
                maxScore = score;
                bestFoundMove = move;  
            }
        }

        bestMove = bestFoundMove;  
        return maxScore;
    }

    int negamaxAB(Board &board, int depth, int alpha, int beta, Move &bestMove) {
        if (depth == 0) {
            return eval::evaluate(board);  // Evaluate leaf node
        }

        int maxScore = -1000000;
        Move bestFoundMove; 

        std::vector<Move> moves = Movegen::generateValidMoves(
            board, board.getIsWhiteTurn() ? Color::WHITE : Color::BLACK
        );

        if (moves.empty()) {  // No legal moves: checkmate or stalemate
            return Movegen::isCheck(
                board, board.getIsWhiteTurn() ? Color::WHITE : Color::BLACK
            ) ? -100000 : 0;  
        }

        for (Move move : moves) {
            board.makeMove(move);
            Move tempMove;  // Store best move for the recursive call
            int score = -negamaxAB(board, depth - 1, -beta, -alpha, tempMove);
            board.unmakeMove(move);

            if (score > maxScore) {
                maxScore = score;
                bestFoundMove = move;
            }
            
            // Update alpha, because we have found a new best move
            if (score > alpha) {
                alpha = score;
            }
            
            // Beta cutoff: if the current score is greater than or equal to beta, prune.
            if (alpha >= beta) {
                break;
            }
        }

        bestMove = bestFoundMove;
        return maxScore;
    }



}
}