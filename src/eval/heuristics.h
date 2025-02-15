#include "core/definitions.h"
#include "core/board.h"
#include "core/movegen.h"

namespace chess{

namespace heuristics{
    
    // Piece values for evaluation
    const int WHITE_PAWN_VALUE = 100;
    const int BLACK_PAWN_VALUE = -100;
    const int WHITE_KNIGHT_VALUE = 320;
    const int BLACK_KNIGHT_VALUE = -320;
    const int WHITE_BISHOP_VALUE = 330;
    const int BLACK_BISHOP_VALUE = -330;
    const int WHITE_ROOK_VALUE = 500;
    const int BLACK_ROOK_VALUE = -500;
    const int WHITE_QUEEN_VALUE = 900;
    const int BLACK_QUEEN_VALUE = -900;
    const int WHITE_KING_VALUE = 20000;
    const int BLACK_KING_VALUE = -20000;
    constexpr std::array<int, 12> pieceValues = {
        WHITE_PAWN_VALUE, WHITE_KNIGHT_VALUE, WHITE_BISHOP_VALUE, WHITE_ROOK_VALUE, WHITE_QUEEN_VALUE, WHITE_KING_VALUE,
        BLACK_PAWN_VALUE, BLACK_KNIGHT_VALUE, BLACK_BISHOP_VALUE, BLACK_ROOK_VALUE, BLACK_QUEEN_VALUE, BLACK_KING_VALUE
    };

    


    int pieceValue(Board &board, Square square);





}
}