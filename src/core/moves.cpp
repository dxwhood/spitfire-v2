#include "core/moves.h"
#include <iostream>

namespace chess {


namespace Moves {

    uint64_t pseudoLegal(Board &board, Square square){
        switch(board.getPieceType(square)){
            using enum PieceType;
            case WHITE_PAWN:
            case BLACK_PAWN:
                return pawnPseudo(board, square);
            case WHITE_KNIGHT:
            case BLACK_KNIGHT:
                return knightPseudo(board, square);
            case WHITE_BISHOP:
            case BLACK_BISHOP:
                return bishopPseudo(board, square);
            case WHITE_ROOK:
            case BLACK_ROOK:
                return rookPseudo(board, square);
            case WHITE_QUEEN:
            case BLACK_QUEEN:
                return queenPseudo(board, square);
            case WHITE_KING:
            case BLACK_KING:
                return kingPseudo(board, square);
            default:
                return 0ULL;
        }
    }

    uint64_t kingPseudo(Board &board, Square square){

        Color color = board.getPieceColor(square);
        uint64_t kingMask = chess::Moves::KING_MOVES[enumToInt(square)];
        uint64_t occupancy = (color == Color::WHITE)? board.getWhiteOccupancy() : board.getBlackOccupancy();
        return kingMask & ~occupancy;
    }

    uint64_t knightPseudo(Board &board, Square square){
        Color color = board.getPieceColor(square);
        uint64_t knightMask = chess::Moves::KNIGHT_MOVES[enumToInt(square)];
        uint64_t occupancy = (color == Color::WHITE)? board.getWhiteOccupancy() : board.getBlackOccupancy();
        return knightMask & ~occupancy;
    }


    uint64_t pawnPseudo(Board &board, Square square){
        Color color = board.getPieceColor(square);
        uint64_t occupancy = (color == Color::WHITE)? board.getWhiteOccupancy() : board.getBlackOccupancy();
        return 0;
    }


    uint64_t rookPseudo(Board &board, Square square){
        Color color = board.getPieceColor(square);
        uint64_t occupancy = (color == Color::WHITE)? board.getWhiteOccupancy() : board.getBlackOccupancy();
        return 0;
    }

    uint64_t bishopPseudo(Board &board, Square square){
        Color color = board.getPieceColor(square);
        uint64_t occupancy = (color == Color::WHITE)? board.getWhiteOccupancy() : board.getBlackOccupancy();
        return 0;
    }

    uint64_t queenPseudo(Board &board, Square square){
        Color color = board.getPieceColor(square);
        uint64_t occupancy = (color == Color::WHITE)? board.getWhiteOccupancy() : board.getBlackOccupancy();
        return 0;
    }


}

}