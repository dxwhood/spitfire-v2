#pragma once

#include <cstdint>  // Standard integer types
#include <array>
#include <string>


namespace chess {

// File bitboards
constexpr uint64_t A_FILE = 0x0101010101010101ULL;
constexpr uint64_t B_FILE = 0x0202020202020202ULL;
constexpr uint64_t C_FILE = 0x0404040404040404ULL;
constexpr uint64_t D_FILE = 0x0808080808080808ULL;
constexpr uint64_t E_FILE = 0x1010101010101010ULL;
constexpr uint64_t F_FILE = 0x2020202020202020ULL;
constexpr uint64_t G_FILE = 0x4040404040404040ULL;
constexpr uint64_t H_FILE = 0x8080808080808080ULL;

// Rank bitboards
constexpr uint64_t RANK_1 = 0x00000000000000FFULL;
constexpr uint64_t RANK_2 = 0x000000000000FF00ULL;
constexpr uint64_t RANK_3 = 0x0000000000FF0000ULL;
constexpr uint64_t RANK_4 = 0x00000000FF000000ULL;
constexpr uint64_t RANK_5 = 0x000000FF00000000ULL;
constexpr uint64_t RANK_6 = 0x0000FF0000000000ULL;
constexpr uint64_t RANK_7 = 0x00FF000000000000ULL;
constexpr uint64_t RANK_8 = 0xFF00000000000000ULL;

// Primary diagonal and antidiagonal bitboards
constexpr uint64_t DIAGONAL_A1_H8 = 0x8040201008040201ULL;
constexpr uint64_t DIAGONAL_H1_A8 = 0x0102040810204080ULL;

// Starting position bitboards
constexpr std::array<uint64_t, 12> STARTING_POSITIONS = {
    0x000000000000FF00ULL, 0x0000000000000042ULL, 0x0000000000000024ULL, 0x0000000000000081ULL,
    0x0000000000000008ULL, 0x0000000000000010ULL, 0x00FF000000000000ULL, 0x4200000000000000ULL,
    0x2400000000000000ULL, 0x8100000000000000ULL, 0x0800000000000000ULL, 0x1000000000000000ULL
};

// Mid game position for debugging
constexpr std::array<uint64_t, 12> MID_GAME_POSITIONS = {
    // White Pieces:
    0x210040000ULL,   // Pawns on e4, c3, f5
    0x400800ULL,      // Knights on d2, g3
    0x4000200ULL,     // Bishops on c4, b2
    0x80000001ULL,    // Rooks on a1, h4
    0x80000ULL,       // Queen on d3
    0x40ULL,          // King on g1

    // Black Pieces:
    0x81000000000ULL,       // Pawns on d6, e5
    0x40000020000000ULL,    // Knights on b5, g7
    0x10008000000000ULL,    // Bishops on e7, h5
    0x1800000000000ULL,     // Rooks on a7, h6
    0x800000000000000ULL,   // Queen on d8
    0x2000000000000000ULL   // King on f8
};

// Squares
enum class Square : int {
    A1 = 0, B1, C1, D1, E1, F1, G1, H1,
    A2 = 8, B2, C2, D2, E2, F2, G2, H2,
    A3 = 16, B3, C3, D3, E3, F3, G3, H3,
    A4 = 24, B4, C4, D4, E4, F4, G4, H4,
    A5 = 32, B5, C5, D5, E5, F5, G5, H5,
    A6 = 40, B6, C6, D6, E6, F6, G6, H6,
    A7 = 48, B7, C7, D7, E7, F7, G7, H7,
    A8 = 56, B8, C8, D8, E8, F8, G8, H8
};

// Piece Types
enum class PieceType : int {
    WHITE_PAWN, WHITE_KNIGHT, WHITE_BISHOP, WHITE_ROOK, WHITE_QUEEN, WHITE_KING,
    BLACK_PAWN, BLACK_KNIGHT, BLACK_BISHOP, BLACK_ROOK, BLACK_QUEEN, BLACK_KING
};

// Helper Array for pieceType to String conversion
constexpr std::array<const char*, 12> pieceNames = {
    "White Pawn", "White Knight", "White Bishop", "White Rook", "White Queen", "White King",
    "Black Pawn", "Black Knight", "Black Bishop", "Black Rook", "Black Queen", "Black King"
};

// Helper Array for pieceType to Char conversion
constexpr std::array<const char, 12> pieceChars = {
    'P', 'N', 'B', 'R', 'Q', 'K',
    'p', 'n', 'b', 'r', 'q', 'k'
};

// Helper Array for pieceType to Unicode conversion
constexpr std::array<const char*, 12> pieceUnicode = {
    "♙", "♘", "♗", "♖", "♕", "♔",  // White pieces
    "♟", "♞", "♝", "♜", "♛", "♚"   // Black pieces
};


// Colors
enum class Color : int {
    WHITE, BLACK
};

// Converts enum classes instances to their int equivalent
template <typename Enum>
constexpr int enumToInt(Enum e) {
    return static_cast<int>(e);
}

inline bool getBit(uint64_t board, uint8_t pos){
    return ((1ULL << pos) & board) != 0;
}

inline void setBit(uint64_t &board, uint8_t pos){
    board |= (1ULL << pos);
}

inline void clearBit(uint64_t &board, uint8_t pos){
    board &= ~(1ULL << pos);
}


class Board {
public:
    Board();  // Constructor
    void printBoard() const;  // Prints the board for debugging
    void printBoard(Square highlightSquare, uint64_t movesBitboard = 0ULL, bool highlight = true) const;
    void clearBoard();  // Clears the board

    void printPiece(PieceType piece) const;  // Prints a bitboard for debugging
    void printBitboard(uint64_t bitboard) const;  // Prints a bitboard for debugging
    void setPieceType(uint64_t bitboard, PieceType piece); // Sets a piece type on the board based on a bitboard
    void clearPieceType(uint64_t bitboard, PieceType piece); // Clears a piece type on the board based on a bitboard
    void setPiece(Square square, PieceType piece);  // Sets a piece on the board
    void clearPiece(Square square);  // Clears a piece on the board
    void setDefaultPosition();  // Sets the default starting position
    void setDebugPosition();  // Sets the mid game position for debugging
    uint64_t getPieceType(PieceType piece) const;  // Returns the bitboard for a piece type
    uint64_t getOccupancy() const;
    uint64_t getEmpty() const;
    uint64_t getWhiteOccupancy() const;
    uint64_t getBlackOccupancy() const;
    

private:
    uint64_t bitboards[12];  // Bitboard for each piece type
};



}  // namespace chess
