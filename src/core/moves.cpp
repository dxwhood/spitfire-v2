#include "core/moves.h"  // Includes move generation logic
#include <iostream>

namespace chess {

namespace Moves {

    uint64_t pseudoLegal(const Board &board, Square square){
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

    uint64_t kingPseudo(const Board &board, Square square){

        Color color = board.getPieceColor(square);
        uint64_t kingMask = chess::Moves::KING_MOVES[enumToInt(square)];
        uint64_t occupancy = (color == Color::WHITE)? board.getWhiteOccupancy() : board.getBlackOccupancy();
        return kingMask & ~occupancy;
    }

    uint64_t knightPseudo(const Board &board, Square square){
        Color color = board.getPieceColor(square);
        uint64_t knightMask = chess::Moves::KNIGHT_MOVES[enumToInt(square)];
        uint64_t occupancy = (color == Color::WHITE)? board.getWhiteOccupancy() : board.getBlackOccupancy();
        return knightMask & ~occupancy;
    }


    uint64_t pawnPseudo(const Board &board, Square square){
        Color color = board.getPieceColor(square);
        Rank rank = getRank(square);
        File file = getFile(square);
        uint64_t occupied_all = board.getOccupancy();
        uint64_t occupied_foe = (color == Color::WHITE)? board.getBlackOccupancy() : board.getWhiteOccupancy();
        uint64_t captures = (color == Color::WHITE)? W_PAWN_ATTACKS[enumToInt(square)] : B_PAWN_ATTACKS[enumToInt(square)];
        uint64_t moves = 0ULL; // initialize moves

        switch (color){
            using enum Color;
            case WHITE:
                moves |= (1ULL << enumToInt(square) << 8);
                if(rank == Rank::RANK_2 && !getBit(occupied_all, enumToInt(square) + 8)){
                    moves |= (moves << 8);
                }
                break;
                
            case BLACK:
                moves |= (1ULL << enumToInt(square) >> 8);
                if(rank == Rank::RANK_7  && !getBit(occupied_all, enumToInt(square) - 8)){
                    moves |= (moves >> 8);
                }
                break;
        }

        moves &= ~occupied_all;
        moves |= (occupied_foe & captures);

        return moves;
    }


    uint64_t rookPseudo(const Board &board, Square square){
        Color color = board.getPieceColor(square);
        uint64_t occupancy = (color == Color::WHITE)? board.getWhiteOccupancy() : board.getBlackOccupancy();
        return 0;
    }

    uint64_t bishopPseudo(const Board &board, Square square){
        Color color = board.getPieceColor(square);
        uint64_t occupancy = (color == Color::WHITE)? board.getWhiteOccupancy() : board.getBlackOccupancy();
        return 0;
    }

    uint64_t queenPseudo(const Board &board, Square square){
        Color color = board.getPieceColor(square);
        uint64_t occupancy = (color == Color::WHITE)? board.getWhiteOccupancy() : board.getBlackOccupancy();
        return 0;
    }


}

}