#include "core/moves.h"

namespace chess {


namespace Moves {


    uint64_t kingPseudo(Board &board, Square square, Color color){
        uint64_t kingMask = chess::Moves::KING_MOVES[enumToInt(square)];
        uint64_t occupancy = (color == Color::WHITE)? board.getWhiteOccupancy() : board.getBlackOccupancy();
        return kingMask & ~occupancy;
    }

    uint64_t knightPseudo(Board &board, Square square, Color color){
        uint64_t knightMask = chess::Moves::KNIGHT_MOVES[enumToInt(square)];
        uint64_t occupancy = (color == Color::WHITE)? board.getWhiteOccupancy() : board.getBlackOccupancy();
        return knightMask & ~occupancy;
    }

    



}

}