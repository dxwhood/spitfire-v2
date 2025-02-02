#pragma once

#include <cstdint>  // Standard integer types
#include <array>
#include <string>
#include <iostream>


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

constexpr std::array<uint64_t, 8> FILE_MASKS = {
    A_FILE, B_FILE, C_FILE, D_FILE, E_FILE, F_FILE, G_FILE, H_FILE
};

// Rank bitboards
constexpr uint64_t RANK_1 = 0x00000000000000FFULL;
constexpr uint64_t RANK_2 = 0x000000000000FF00ULL;
constexpr uint64_t RANK_3 = 0x0000000000FF0000ULL;
constexpr uint64_t RANK_4 = 0x00000000FF000000ULL;
constexpr uint64_t RANK_5 = 0x000000FF00000000ULL;
constexpr uint64_t RANK_6 = 0x0000FF0000000000ULL;
constexpr uint64_t RANK_7 = 0x00FF000000000000ULL;
constexpr uint64_t RANK_8 = 0xFF00000000000000ULL;

constexpr std::array<uint64_t, 8> RANK_MASKS = {
    RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8
};

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

// Files
enum class File : int {
    A_FILE, B_FILE, C_FILE, D_FILE, E_FILE, F_FILE, G_FILE, H_FILE
};

// Ranks

enum class Rank: int {
    RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8
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

// File/Rank/Square conversions
constexpr File getFile(Square square) {
    return static_cast<File>(static_cast<int>(square) % 8);
}

constexpr Rank getRank(Square square) {
    return static_cast<Rank>(static_cast<int>(square) / 8);
}

constexpr Square getSquare(File file, Rank rank) {
    return static_cast<Square>(static_cast<int>(rank) * 8 + static_cast<int>(file));
}

// Piece Types
enum class PieceType : int {
    WHITE_PAWN, WHITE_KNIGHT, WHITE_BISHOP, WHITE_ROOK, WHITE_QUEEN, WHITE_KING,
    BLACK_PAWN, BLACK_KNIGHT, BLACK_BISHOP, BLACK_ROOK, BLACK_QUEEN, BLACK_KING
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
    void clearBoard();  // Clears the board

    void setPieces(uint64_t bitboard, PieceType piece); // Sets a piece type on the board based on a bitboard
    void clearPieceType(uint64_t bitboard, PieceType piece); // Clears a piece type on the board based on a bitboard
    void setPiece(Square square, PieceType piece);  // Sets a piece on the board
    void clearPiece(Square square);  // Clears a piece on the board
    void setDefaultPosition();  // Sets the default starting position
    void setDebugPosition();  // Sets the mid game position for debugging

    Color getPieceColor(Square square) const;  // Returns the color of a piece on a square
    PieceType getPieceType(Square square) const;  // Returns the piece type on a square

    uint64_t getAllPieces(PieceType piece) const;  // Returns the bitboard for a piece type
    uint64_t getOccupancy() const;
    uint64_t getEmpty() const;
    uint64_t getWhiteOccupancy() const;
    uint64_t getBlackOccupancy() const;

    std::array<uint64_t, 12> getBitboards() const;
    

private:
    std::array<uint64_t, 12> bitboards;  // Bitboard for each piece type
};



}  // namespace chess
