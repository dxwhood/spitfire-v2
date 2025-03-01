#pragma once

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
const int WHITE_KING_VALUE = 50000;
const int BLACK_KING_VALUE = -50000;
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

// Pawn Structure
constexpr std::array<int, 8> PASSED_PAWN_BONUS_WHITE = {0, 10, 20, 50, 100, 200, 400, 900};
constexpr std::array<int, 8> PASSED_PAWN_BONUS_BLACK = {900, 400, 200, 100, 50, 20, 10, 0};

constexpr std::array<int, 8> ISOLATED_PAWN_PENALTY_WHITE = {-15, -20, -25, -25, -20, -15, -5, 0};
constexpr std::array<int, 8> ISOLATED_PAWN_PENALTY_BLACK = {0, -5, -15, -20, -25, -25, -20, -15};

constexpr std::array<int, 8> DOUBLED_PAWN_PENALTY = {0, -50, -100, -150, -200, -250, -300, -350};

