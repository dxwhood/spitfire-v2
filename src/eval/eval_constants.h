#include "core/definitions.h"


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
constexpr std::array<int, 12> PIECE_VALUES = {
    WHITE_PAWN_VALUE, WHITE_KNIGHT_VALUE, WHITE_BISHOP_VALUE, WHITE_ROOK_VALUE, WHITE_QUEEN_VALUE, WHITE_KING_VALUE,
    BLACK_PAWN_VALUE, BLACK_KNIGHT_VALUE, BLACK_BISHOP_VALUE, BLACK_ROOK_VALUE, BLACK_QUEEN_VALUE, BLACK_KING_VALUE
};


// Piece square tables
constexpr std::array<int,64> WHITE_PAWN_TABLE_MG = {
    0, 0, 0, 0, 0, 0, 0, 0,
    50, 50, 50, 50, 50, 50, 50, 50,
    10, 10, 20, 30, 30, 20, 10, 10,
    5, 5, 10, 25, 25, 10, 5, 5,
    0, 0, 0, 20, 20, 0, 0, 0,
    5, -5, -10, 0, 0, -10, -5, 5,
    5, 10, 10, -20, -20, 10, 10, 5,
    0, 0, 0, 0, 0, 0, 0, 0
};


constexpr std::array<int,64> BLACK_PAWN_TABLE_MG = {
    0, 0, 0, 0, 0, 0, 0, 0,
    5, 10, 10, -20, -20, 10, 10, 5,
    5, -5, -10, 0, 0, -10, -5, 5,
    0, 0, 0, 20, 20, 0, 0, 0,
    5, 5, 10, 25, 25, 10, 5, 5,
    10, 10, 20, 30, 30, 20, 10, 10,
    50, 50, 50, 50, 50, 50, 50, 50,
    0, 0, 0, 0, 0, 0, 0, 0
};


constexpr std::array<int,64> WHITE_KNIGHT_TABLE_MG = {
    -50, -40, -30, -30, -30, -30, -40, -50,
    -40, -20, 0, 0, 0, 0, -20, -40,
    -30, 0, 10, 15, 15, 10, 0, -30,
    -30, 5, 15, 20, 20, 15, 5, -30,
    -30, 0, 15, 20, 20, 15, 0, -30,
    -30, 5, 10, 15, 15, 10, 5, -30,
    -40, -20, 0, 5, 5, 0, -20, -40,
    -50, -40, -30, -30, -30, -30, -40, -50
};

constexpr std::array<int,64> BLACK_KNIGHT_TABLE_MG = {
    -50, -40, -30, -30, -30, -30, -40, -50,
    -40, -20, 0, 5, 5, 0, -20, -40,
    -30, 5, 10, 15, 15, 10, 5, -30,
    -30, 0, 15, 20, 20, 15, 0, -30,
    -30, 5, 15, 20, 20, 15, 5, -30,
    -30, 0, 10, 15, 15, 10, 0, -30,
    -40, -20, 0, 0, 0, 0, -20, -40,
    -50, -40, -30, -30, -30, -30, -40, -50
};

constexpr std::array<int,64> WHITE_BISHOP_TABLE_MG = {
    -20, -10, -10, -10, -10, -10, -10, -20,
    -10, 0, 0, 0, 0, 0, 0, -10,
    -10, 0, 5, 10, 10, 5, 0, -10,
    -10, 5, 5, 10, 10, 5, 5, -10,
    -10, 0, 10, 10, 10, 10, 0, -10,
    -10, 10, 10, 10, 10, 10, 10, -10,
    -10, 5, 0, 0, 0, 0, 5, -10,
    -20, -10, -10, -10, -10, -10, -10, -20
};

constexpr std::array<int,64> BLACK_BISHOP_TABLE_MG = {
    -20, -10, -10, -10, -10, -10, -10, -20,
    -10, 5, 0, 0, 0, 0, 5, -10,
    -10, 10, 10, 10, 10, 10, 10, -10,
    -10, 0, 10, 10, 10, 10, 0, -10,
    -10, 5, 5, 10, 10, 5, 5, -10,
    -10, 0, 5, 10, 10, 5, 0, -10,
    -10, 0, 0, 0, 0, 0, 0, -10,
    -20, -10, -10, -10, -10, -10, -10, -20
};

constexpr std::array<int,64> WHITE_ROOK_TABLE_MG = {
    0, 0, 0, 0, 0, 0, 0, 0,
    5, 10, 10, 10, 10, 10, 10, 5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    0, 0, 0, 5, 5, 0, 0, 0
};

constexpr std::array<int,64> BLACK_ROOK_TABLE_MG = {
    0, 0, 0, 5, 5, 0, 0, 0,
    -5, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, 0, 0, 0, 0, 0, -5,
    5, 10, 10, 10, 10, 10, 10, 5,
    0, 0, 0, 0, 0, 0, 0, 0
};

constexpr std::array<int,64> WHITE_QUEEN_TABLE_MG = {
    -20, -10, -10, -5, -5, -10, -10, -20,
    -10, 0, 0, 0, 0, 0, 0, -10,
    -10, 0, 5, 5, 5, 5, 0, -10,
    -5, 0, 5, 5, 5, 5, 0, -5,
     0, 0, 5, 5, 5, 5, 0, -5,
    -10, 5, 5, 5, 5, 5, 0, -10,
    -10, 0, 5, 0, 0, 0, 0, -10,
    -20, -10, -10, -5, -5, -10, -10, -20
};

constexpr std::array<int,64> BLACK_QUEEN_TABLE_MG = {
    -20, -10, -10, -5, -5, -10, -10, -20,
    -10, 0, 5, 0, 0, 0, 0, -10,
    -10, 5, 5, 5, 5, 5, 0, -10,
      0, 0, 5, 5, 5, 5, 0, -5,
     -5, 0, 5, 5, 5, 5, 0, -5,
    -10, 0, 5, 5, 5, 5, 0, -10,
    -10, 0, 0, 0, 0, 0, 0, -10,
    -20, -10, -10, -5, -5, -10, -10, -20
};

constexpr std::array<int,64> WHITE_KING_TABLE_MG = {
     20,  30,  10,   0,   0,  10,  30,  20,
     20,  20,   0,   0,   0,   0,  20,  20,
    -10, -20, -20, -20, -20, -20, -20, -10,
    -20, -30, -30, -40, -40, -30, -30, -20,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30
};

constexpr std::array<int,64> BLACK_KING_TABLE_MG = {
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -20, -30, -30, -40, -40, -30, -30, -20,
    -10, -20, -20, -20, -20, -20, -20, -10,
     20,  20,   0,   0,   0,   0,  20,  20,
     20,  30,  10,   0,   0,  10,  30,  20
};

constexpr std::array<std::array<int, 64>, 12> PIECE_SQUARE_TABLES_MG = {
    WHITE_PAWN_TABLE_MG, WHITE_KNIGHT_TABLE_MG, WHITE_BISHOP_TABLE_MG, WHITE_ROOK_TABLE_MG, WHITE_QUEEN_TABLE_MG, WHITE_KING_TABLE_MG,
    BLACK_PAWN_TABLE_MG, BLACK_KNIGHT_TABLE_MG, BLACK_BISHOP_TABLE_MG, BLACK_ROOK_TABLE_MG, BLACK_QUEEN_TABLE_MG, BLACK_KING_TABLE_MG
};

constexpr std::array<int, 64> WHITE_PAWN_TABLE_EG = {
      0,  0,  0,  0,  0,  0,  0,  0,     // Rank 1
     10, 10, 10, 10, 10, 10, 10, 10,     // Rank 2
     20, 20, 20, 20, 20, 20, 20, 20,    // Rank 3
     30, 30, 30, 40, 40, 30, 30, 30,    // Rank 4
     40, 40, 40, 50, 50, 40, 40, 40,    // Rank 5
     50, 50, 50, 60, 60, 50, 50, 50,   // Rank 6
     60, 60, 60, 70, 70, 60, 60, 60,   // Rank 7
      0,  0,  0,  0,  0,  0,  0,  0    // Rank 8
};


constexpr std::array<int, 64> BLACK_PAWN_TABLE_EG = {
    // Rank 1
      0,  0,  0,  0,  0,  0,  0,  0,
    // Rank 2
     60, 60, 60, 70, 70, 60, 60, 60,
    // Rank 3
     50, 50, 50, 60, 60, 50, 50, 50,
    // Rank 4
     40, 40, 40, 50, 50, 40, 40, 40,
    // Rank 5
     30, 30, 30, 40, 40, 30, 30, 30,
    // Rank 6
     20, 20, 20, 20, 20, 20, 20, 20,
    // Rank 7
     10, 10, 10, 10, 10, 10, 10, 10,
    // Rank 8
      0,  0,  0,  0,  0,  0,  0,  0
};

constexpr std::array<int, 64> WHITE_KNIGHT_TABLE_EG = {
    // Rank 1
   -60, -50, -40, -40, -40, -40, -50, -60,
    // Rank 2
   -50, -30, -20, -15, -15, -20, -30, -50,
    // Rank 3
   -40, -20,   0,   5,   5,   0, -20, -40,
    // Rank 4
   -40, -15,   5,  10,  10,   5, -15, -40,
    // Rank 5
   -40, -15,   5,  10,  10,   5, -15, -40,
    // Rank 6
   -40, -20,   0,   5,   5,   0, -20, -40,
    // Rank 7
   -50, -30, -20, -15, -15, -20, -30, -50,
    // Rank 8
   -60, -50, -40, -40, -40, -40, -50, -60
};

constexpr std::array<int, 64> BLACK_KNIGHT_TABLE_EG = {
    // Rank 1
   -60, -50, -40, -40, -40, -40, -50, -60,
    // Rank 2
   -50, -30, -20, -15, -15, -20, -30, -50,
    // Rank 3
   -40, -20,   0,   5,   5,   0, -20, -40,
    // Rank 4
   -40, -15,   5,  10,  10,   5, -15, -40,
    // Rank 5
   -40, -15,   5,  10,  10,   5, -15, -40,
    // Rank 6
   -40, -20,   0,   5,   5,   0, -20, -40,
    // Rank 7
   -50, -30, -20, -15, -15, -20, -30, -50,
    // Rank 8
   -60, -50, -40, -40, -40, -40, -50, -60
};

constexpr std::array<int, 64> WHITE_BISHOP_TABLE_EG = {
    // Rank 1
   -20, -10, -10, -10, -10, -10, -10, -20,
    // Rank 2
   -10,   0,   0,   0,   0,   0,   0, -10,
    // Rank 3
   -10,   0,  15,  20,  20,  15,   0, -10,
    // Rank 4
   -10,   5,  20,  25,  25,  20,   5, -10,
    // Rank 5
   -10,   0,  20,  25,  25,  20,   0, -10,
    // Rank 6
   -10,   0,  15,  20,  20,  15,   0, -10,
    // Rank 7
   -10,   0,   0,   0,   0,   0,   0, -10,
    // Rank 8
   -20, -10, -10, -10, -10, -10, -10, -20
};

constexpr std::array<int, 64> BLACK_BISHOP_TABLE_EG = {
    // Rank 1
   -20, -10, -10, -10, -10, -10, -10, -20,
    // Rank 2
   -10,   0,   0,   0,   0,   0,   0, -10,
    // Rank 3
   -10,   0,  15,  20,  20,  15,   0, -10,
    // Rank 4
   -10,   5,  20,  25,  25,  20,   5, -10,
    // Rank 5
   -10,   0,  20,  25,  25,  20,   0, -10,
    // Rank 6
   -10,   0,  15,  20,  20,  15,   0, -10,
    // Rank 7
   -10,   0,   0,   0,   0,   0,   0, -10,
    // Rank 8
   -20, -10, -10, -10, -10, -10, -10, -20
};

constexpr std::array<int, 64> WHITE_ROOK_TABLE_EG = {
    // Rank 1
      0,   0,   0,  10,  10,   0,   0,   0,
    // Rank 2
      5,  10,  10,  15,  15,  10,  10,   5,
    // Rank 3
      0,   0,   0,  10,  10,   0,   0,   0,
    // Rank 4
      0,   0,   0,  10,  10,   0,   0,   0,
    // Rank 5
      0,   0,   0,  10,  10,   0,   0,   0,
    // Rank 6
      0,   0,   0,  10,  10,   0,   0,   0,
    // Rank 7
      5,  10,  10,  15,  15,  10,  10,   5,
    // Rank 8
      0,   0,   0,  10,  10,   0,   0,   0
};

constexpr std::array<int, 64> BLACK_ROOK_TABLE_EG = {
    // Rank 1
      0,   0,   0,  10,  10,   0,   0,   0,
    // Rank 2
      5,  10,  10,  15,  15,  10,  10,   5,
    // Rank 3
      0,   0,   0,  10,  10,   0,   0,   0,
    // Rank 4
      0,   0,   0,  10,  10,   0,   0,   0,
    // Rank 5
      0,   0,   0,  10,  10,   0,   0,   0,
    // Rank 6
      0,   0,   0,  10,  10,   0,   0,   0,
    // Rank 7
      5,  10,  10,  15,  15,  10,  10,   5,
    // Rank 8
      0,   0,   0,  10,  10,   0,   0,   0
};

constexpr std::array<int, 64> WHITE_QUEEN_TABLE_EG = {
    // Rank 1
   -20, -10, -10,  -5,  -5, -10, -10, -20,
    // Rank 2
   -10,   0,   5,   5,   5,   5,   0, -10,
    // Rank 3
   -10,   5,   5,  10,  10,   5,   5, -10,
    // Rank 4
    -5,   5,  10,  15,  15,  10,   5,  -5,
    // Rank 5
    -5,   5,  10,  15,  15,  10,   5,  -5,
    // Rank 6
   -10,   5,   5,  10,  10,   5,   5, -10,
    // Rank 7
   -10,   0,   5,   5,   5,   5,   0, -10,
    // Rank 8
   -20, -10, -10,  -5,  -5, -10, -10, -20
};

constexpr std::array<int, 64> BLACK_QUEEN_TABLE_EG = {
    // Rank 1
   -20, -10, -10,  -5,  -5, -10, -10, -20,
    // Rank 2
   -10,   0,   5,   5,   5,   5,   0, -10,
    // Rank 3
   -10,   5,   5,  10,  10,   5,   5, -10,
    // Rank 4
    -5,   5,  10,  15,  15,  10,   5,  -5,
    // Rank 5
    -5,   5,  10,  15,  15,  10,   5,  -5,
    // Rank 6
   -10,   5,   5,  10,  10,   5,   5, -10,
    // Rank 7
   -10,   0,   5,   5,   5,   5,   0, -10,
    // Rank 8
   -20, -10, -10,  -5,  -5, -10, -10, -20
};


constexpr std::array<int, 64> WHITE_KING_TABLE_EG = {
    // Rank 1
   -40, -30, -20, -10, -10, -20, -30, -40,
    // Rank 2
   -30, -20, -10,   0,   0, -10, -20, -30,
    // Rank 3
   -20, -10,  10,  20,  20,  10, -10, -20,
    // Rank 4
   -10,   0,  20,  30,  30,  20,   0, -10,
    // Rank 5
   -10,   0,  20,  30,  30,  20,   0, -10,
    // Rank 6
   -20, -10,  10,  20,  20,  10, -10, -20,
    // Rank 7
   -30, -20, -10,   0,   0, -10, -20, -30,
    // Rank 8
   -40, -30, -20, -10, -10, -20, -30, -40
};

constexpr std::array<int, 64> BLACK_KING_TABLE_EG = {
    // Rank 1
   -40, -30, -20, -10, -10, -20, -30, -40,
    // Rank 2
   -30, -20, -10,   0,   0, -10, -20, -30,
    // Rank 3
   -20, -10,  10,  20,  20,  10, -10, -20,
    // Rank 4
   -10,   0,  20,  30,  30,  20,   0, -10,
    // Rank 5
   -10,   0,  20,  30,  30,  20,   0, -10,
    // Rank 6
   -20, -10,  10,  20,  20,  10, -10, -20,
    // Rank 7
   -30, -20, -10,   0,   0, -10, -20, -30,
    // Rank 8
   -40, -30, -20, -10, -10, -20, -30, -40
};

constexpr std::array<std::array<int, 64>, 12> PIECE_SQUARE_TABLES_EG = {
    WHITE_PAWN_TABLE_EG, WHITE_KNIGHT_TABLE_EG, WHITE_BISHOP_TABLE_EG, WHITE_ROOK_TABLE_EG, WHITE_QUEEN_TABLE_EG, WHITE_KING_TABLE_EG,
    BLACK_PAWN_TABLE_EG, BLACK_KNIGHT_TABLE_EG, BLACK_BISHOP_TABLE_EG, BLACK_ROOK_TABLE_EG, BLACK_QUEEN_TABLE_EG, BLACK_KING_TABLE_EG
};


// Mobility Weights
constexpr std::array<int,28> KNIGHT_MOBILITY_MG = {-30, -20, -10,  0,  5,  10,  15,  20,  25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
constexpr std::array<int,28> KNIGHT_MOBILITY_EG = {-20, -15,  -5,  0,  5,  10,  15,  20,  25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

constexpr std::array<int,28> BISHOP_MOBILITY_MG = {-10, -5,  0,  5,  10,  15,  20,  25,  30,  35,  40,  45,  50,  55, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
constexpr std::array<int,28> BISHOP_MOBILITY_EG = {  0,  5,  10,  15,  20,  25,  30,  35,  40,  45,  50,  55,  60,  65, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

constexpr std::array<int,28> ROOK_MOBILITY_MG = {-15, -10, -5,  0,  5,  10,  15,  20,  25,  30,  35,  40,  45,  50,  55, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
constexpr std::array<int,28> ROOK_MOBILITY_EG = {-10, -5,   0,  5,  10,  15,  20,  25,  30,  35,  40,  45,  50,  55,  60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

constexpr std::array<int,28> QUEEN_MOBILITY_MG = {-10, -5,  0,  5,  10,  15,  20,  25,  30,  35,  40,  45,  50,  55,  60,  65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125};
constexpr std::array<int,28> QUEEN_MOBILITY_EG = { -5,  0,  5, 10,  15,  20,  25,  30,  35,  40,  45,  50,  55,  60,  65,  70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125, 130};

constexpr std::array<int,28> KING_MOBILITY_MG = {-40, -30, -20, -10,  0,  5,  10,  15,  20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
constexpr std::array<int,28> KING_MOBILITY_EG = {-10,  0,  10,  20,  30,  40,  50,  60,  70, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

constexpr std::array<int,28> PAWN_MOBILITY_NULL = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Compiled mobility table for all PieceTypes 
constexpr std::array<std::array<int, 28>, 12> MOBILITY_TABLES_MG = {
    PAWN_MOBILITY_NULL, KNIGHT_MOBILITY_MG, BISHOP_MOBILITY_MG, ROOK_MOBILITY_MG, QUEEN_MOBILITY_MG, KING_MOBILITY_MG,
    PAWN_MOBILITY_NULL, KNIGHT_MOBILITY_MG, BISHOP_MOBILITY_MG, ROOK_MOBILITY_MG, QUEEN_MOBILITY_MG, KING_MOBILITY_MG
};

constexpr std::array<std::array<int, 28>, 12> MOBILITY_TABLES_EG = {
    PAWN_MOBILITY_NULL, KNIGHT_MOBILITY_EG, BISHOP_MOBILITY_EG, ROOK_MOBILITY_EG, QUEEN_MOBILITY_EG, KING_MOBILITY_EG,
    PAWN_MOBILITY_NULL, KNIGHT_MOBILITY_EG, BISHOP_MOBILITY_EG, ROOK_MOBILITY_EG, QUEEN_MOBILITY_EG, KING_MOBILITY_EG
};

// King Safety

// Pawn Shield Strength
constexpr std::array<int, 4> PAWN_SHIELD_STRENGTH = {0, 20, 40, 80};


constexpr uint64_t PAWN_SHIELD_MASKS[64] = {
    [static_cast<size_t>(Square::G1)] = (1ULL << static_cast<size_t>(Square::F2)) | 
                                        (1ULL << static_cast<size_t>(Square::G2)) | 
                                        (1ULL << static_cast<size_t>(Square::H2)),

    [static_cast<size_t>(Square::G8)] = (1ULL << static_cast<size_t>(Square::F7)) | 
                                        (1ULL << static_cast<size_t>(Square::G7)) | 
                                        (1ULL << static_cast<size_t>(Square::H7)),

    [static_cast<size_t>(Square::C1)] = (1ULL << static_cast<size_t>(Square::B2)) | 
                                        (1ULL << static_cast<size_t>(Square::C2)) | 
                                        (1ULL << static_cast<size_t>(Square::D2)),

    [static_cast<size_t>(Square::C8)] = (1ULL << static_cast<size_t>(Square::B7)) | 
                                        (1ULL << static_cast<size_t>(Square::C7)) | 
                                        (1ULL << static_cast<size_t>(Square::D7))
};

// King Danger Zone Masks
constexpr std::array<uint64_t, 64> KING_DANGER_ZONE_MASKS = {
    0x0000000000000302ULL, 0x0000000000000705ULL, 0x0000000000000E0AULL, 0x0000000000001C14ULL,
    0x0000000000003828ULL, 0x0000000000007050ULL, 0x000000000000E0A0ULL, 0x000000000000C040ULL,
    0x0000000000030203ULL, 0x0000000000070507ULL, 0x00000000000E0A0EULL, 0x00000000001C141CULL,
    0x0000000000382838ULL, 0x0000000000705070ULL, 0x0000000000E0A0E0ULL, 0x0000000000C040C0ULL,
    0x0000000003020300ULL, 0x0000000007050700ULL, 0x000000000E0A0E00ULL, 0x000000001C141C00ULL,
    0x0000000038283800ULL, 0x0000000070507000ULL, 0x00000000E0A0E000ULL, 0x00000000C040C000ULL,
    0x0000000302030000ULL, 0x0000000705070000ULL, 0x0000000E0A0E0000ULL, 0x0000001C141C0000ULL,
    0x0000003828380000ULL, 0x0000007050700000ULL, 0x000000E0A0E00000ULL, 0x000000C040C00000ULL,
    0x0000030203000000ULL, 0x0000070507000000ULL, 0x00000E0A0E000000ULL, 0x00001C141C000000ULL,
    0x0000382838000000ULL, 0x0000705070000000ULL, 0x0000E0A0E0000000ULL, 0x0000C040C0000000ULL,
    0x0003020300000000ULL, 0x0007050700000000ULL, 0x000E0A0E00000000ULL, 0x001C141C00000000ULL,
    0x0038283800000000ULL, 0x0070507000000000ULL, 0x00E0A0E000000000ULL, 0x00C040C000000000ULL,
    0x0302030000000000ULL, 0x0705070000000000ULL, 0x0E0A0E0000000000ULL, 0x1C141C0000000000ULL,
    0x3828380000000000ULL, 0x7050700000000000ULL, 0xE0A0E00000000000ULL, 0xC040C00000000000ULL,
    0x0203000000000000ULL, 0x0507000000000000ULL, 0x0A0E000000000000ULL, 0x141C000000000000ULL,
    0x2838000000000000ULL, 0x5070000000000000ULL, 0xA0E0000000000000ULL, 0x40C0000000000000ULL
};
