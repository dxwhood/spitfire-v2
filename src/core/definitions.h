#pragma once

#include <array>
#include <cstdint>
#include <optional>
#include <string>


const int NEG_INF = -1000000000;
const int POS_INF = 1000000000;


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

constexpr std::array<uint64_t, 8> FILE_ADJACENT_MASKS = {
    B_FILE, A_FILE | C_FILE, B_FILE | D_FILE, C_FILE | E_FILE, D_FILE | F_FILE, E_FILE | G_FILE, F_FILE | H_FILE, G_FILE
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

constexpr std::array<uint64_t, 64> DIAGONAL_MASKS = {
    // File A (A1 .. A8)
    0x8040201008040201ULL, 0x0080402010080402ULL, 0x0000804020100804ULL, 0x0000008040201008ULL,
    0x0000000080402010ULL, 0x0000000000804020ULL, 0x0000000000008040ULL, 0x0000000000000080ULL,
    // File B (B1 .. B8)
    0x4020100804020100ULL, 0x8040201008040201ULL, 0x0080402010080402ULL, 0x0000804020100804ULL,
    0x0000008040201008ULL, 0x0000000080402010ULL, 0x0000000000804020ULL, 0x0000000000008040ULL,
    // File C (C1 .. C8)
    0x2010080402010000ULL, 0x4020100804020100ULL, 0x8040201008040201ULL, 0x0080402010080402ULL,
    0x0000804020100804ULL, 0x0000008040201008ULL, 0x0000000080402010ULL, 0x0000000000804020ULL,
    // File D (D1 .. D8)
    0x1008040201000000ULL, 0x2010080402010000ULL, 0x4020100804020100ULL, 0x8040201008040201ULL,
    0x0080402010080402ULL, 0x0000804020100804ULL, 0x0000008040201008ULL, 0x0000000080402010ULL,
    // File E (E1 .. E8)
    0x0804020100000000ULL, 0x1008040201000000ULL, 0x2010080402010000ULL, 0x4020100804020100ULL,
    0x8040201008040201ULL, 0x0080402010080402ULL, 0x0000804020100804ULL, 0x0000008040201008ULL,
    // File F (F1 .. F8)
    0x0402010000000000ULL, 0x0804020100000000ULL, 0x1008040201000000ULL, 0x2010080402010000ULL,
    0x4020100804020100ULL, 0x8040201008040201ULL, 0x0080402010080402ULL, 0x0000804020100804ULL,
    // File G (G1 .. G8)
    0x0201000000000000ULL, 0x0402010000000000ULL, 0x0804020100000000ULL, 0x1008040201000000ULL,
    0x2010080402010000ULL, 0x4020100804020100ULL, 0x8040201008040201ULL, 0x0080402010080402ULL,
    // File H (H1 .. H8)
    0x0100000000000000ULL, 0x0201000000000000ULL, 0x0402010000000000ULL, 0x0804020100000000ULL,
    0x1008040201000000ULL, 0x2010080402010000ULL, 0x4020100804020100ULL, 0x8040201008040201ULL
};

constexpr std::array<uint64_t, 64> ANTIDIAGONAL_MASKS = {
    0x0000000000000001ULL, 0x0000000000000102ULL, 0x0000000000010204ULL, 0x0000000001020408ULL,
    0x0000000102040810ULL, 0x0000010204081020ULL, 0x0001020408102040ULL, 0x0102040810204080ULL,
    0x0000000000000102ULL, 0x0000000000010204ULL, 0x0000000001020408ULL, 0x0000000102040810ULL,
    0x0000010204081020ULL, 0x0001020408102040ULL, 0x0102040810204080ULL, 0x0204081020408000ULL,
    0x0000000000010204ULL, 0x0000000001020408ULL, 0x0000000102040810ULL, 0x0000010204081020ULL,
    0x0001020408102040ULL, 0x0102040810204080ULL, 0x0204081020408000ULL, 0x0408102040800000ULL,
    0x0000000001020408ULL, 0x0000000102040810ULL, 0x0000010204081020ULL, 0x0001020408102040ULL,
    0x0102040810204080ULL, 0x0204081020408000ULL, 0x0408102040800000ULL, 0x0810204080000000ULL,
    0x0000000102040810ULL, 0x0000010204081020ULL, 0x0001020408102040ULL, 0x0102040810204080ULL,
    0x0204081020408000ULL, 0x0408102040800000ULL, 0x0810204080000000ULL, 0x1020408000000000ULL,
    0x0000010204081020ULL, 0x0001020408102040ULL, 0x0102040810204080ULL, 0x0204081020408000ULL,
    0x0408102040800000ULL, 0x0810204080000000ULL, 0x1020408000000000ULL, 0x2040800000000000ULL,
    0x0001020408102040ULL, 0x0102040810204080ULL, 0x0204081020408000ULL, 0x0408102040800000ULL,
    0x0810204080000000ULL, 0x1020408000000000ULL, 0x2040800000000000ULL, 0x4080000000000000ULL,
    0x0102040810204080ULL, 0x0204081020408000ULL, 0x0408102040800000ULL, 0x0810204080000000ULL,
    0x1020408000000000ULL, 0x2040800000000000ULL, 0x4080000000000000ULL, 0x8000000000000000ULL,
};

constexpr std::array<uint64_t, 64> SQUARE_MASKS = {
    0x0000000000000001ULL, 0x0000000000000002ULL, 0x0000000000000004ULL, 0x0000000000000008ULL,
    0x0000000000000010ULL, 0x0000000000000020ULL, 0x0000000000000040ULL, 0x0000000000000080ULL,
    0x0000000000000100ULL, 0x0000000000000200ULL, 0x0000000000000400ULL, 0x0000000000000800ULL,
    0x0000000000001000ULL, 0x0000000000002000ULL, 0x0000000000004000ULL, 0x0000000000008000ULL,
    0x0000000000010000ULL, 0x0000000000020000ULL, 0x0000000000040000ULL, 0x0000000000080000ULL,
    0x0000000000100000ULL, 0x0000000000200000ULL, 0x0000000000400000ULL, 0x0000000000800000ULL,
    0x0000000001000000ULL, 0x0000000002000000ULL, 0x0000000004000000ULL, 0x0000000008000000ULL,
    0x0000000010000000ULL, 0x0000000020000000ULL, 0x0000000040000000ULL, 0x0000000080000000ULL,
    0x0000000100000000ULL, 0x0000000200000000ULL, 0x0000000400000000ULL, 0x0000000800000000ULL,
    0x0000001000000000ULL, 0x0000002000000000ULL, 0x0000004000000000ULL, 0x0000008000000000ULL, 
    0x0000010000000000ULL, 0x0000020000000000ULL, 0x0000040000000000ULL, 0x0000080000000000ULL,
    0x0000100000000000ULL, 0x0000200000000000ULL, 0x0000400000000000ULL, 0x0000800000000000ULL,
    0x0001000000000000ULL, 0x0002000000000000ULL, 0x0004000000000000ULL, 0x0008000000000000ULL,
    0x0010000000000000ULL, 0x0020000000000000ULL, 0x0040000000000000ULL, 0x0080000000000000ULL,
    0x0100000000000000ULL, 0x0200000000000000ULL, 0x0400000000000000ULL, 0x0800000000000000ULL,
    0x1000000000000000ULL, 0x2000000000000000ULL, 0x4000000000000000ULL, 0x8000000000000000ULL
};

// Key Squares bitboards
constexpr uint64_t CENTER_SQUARES = 0x0000001818000000ULL;

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


// Knight move bitboards
constexpr std::array<uint64_t, 64> KNIGHT_MOVES = {
    0x0000000000020400ULL, 0x0000000000050800ULL, 0x00000000000A1100ULL, 0x0000000000142200ULL,
    0x0000000000284400ULL, 0x0000000000508800ULL, 0x0000000000A01000ULL, 0x0000000000402000ULL,
    0x0000000002040004ULL, 0x0000000005080008ULL, 0x000000000A110011ULL, 0x0000000014220022ULL,
    0x0000000028440044ULL, 0x0000000050880088ULL, 0x00000000A0100010ULL, 0x0000000040200020ULL,
    0x0000000204000402ULL, 0x0000000508000805ULL, 0x0000000A1100110AULL, 0x0000001422002214ULL,
    0x0000002844004428ULL, 0x0000005088008850ULL, 0x000000A0100010A0ULL, 0x0000004020002040ULL,
    0x0000020400040200ULL, 0x0000050800080500ULL, 0x00000A1100110A00ULL, 0x0000142200221400ULL,
    0x0000284400442800ULL, 0x0000508800885000ULL, 0x0000A0100010A000ULL, 0x0000402000204000ULL,
    0x0002040004020000ULL, 0x0005080008050000ULL, 0x000A1100110A0000ULL, 0x0014220022140000ULL,
    0x0028440044280000ULL, 0x0050880088500000ULL, 0x00A0100010A00000ULL, 0x0040200020400000ULL,
    0x0204000402000000ULL, 0x0508000805000000ULL, 0x0A1100110A000000ULL, 0x1422002214000000ULL,
    0x2844004428000000ULL, 0x5088008850000000ULL, 0xA0100010A0000000ULL, 0x4020002040000000ULL,
    0x0400040200000000ULL, 0x0800080500000000ULL, 0x1100110A00000000ULL, 0x2200221400000000ULL,
    0x4400442800000000ULL, 0x8800885000000000ULL, 0x100010A000000000ULL, 0x2000204000000000ULL,
    0x0004020000000000ULL, 0x0008050000000000ULL, 0x00110A0000000000ULL, 0x0022140000000000ULL,
    0x0044280000000000ULL, 0x0088500000000000ULL, 0x0010A00000000000ULL, 0x0020400000000000ULL
};

// King move bitboards
constexpr std::array<uint64_t, 64> KING_MOVES = {
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

// White pawn attacks bitboards
constexpr std::array<uint64_t, 64> W_PAWN_ATTACKS = {
    0x0000000000000200ULL, 0x0000000000000500ULL, 0x0000000000000A00ULL, 0x0000000000001400ULL,
    0x0000000000002800ULL, 0x0000000000005000ULL, 0x000000000000A000ULL, 0x0000000000004000ULL,
    0x0000000000020000ULL, 0x0000000000050000ULL, 0x00000000000A0000ULL, 0x0000000000140000ULL,
    0x0000000000280000ULL, 0x0000000000500000ULL, 0x0000000000A00000ULL, 0x0000000000400000ULL,
    0x0000000002000000ULL, 0x0000000005000000ULL, 0x000000000A000000ULL, 0x0000000014000000ULL,
    0x0000000028000000ULL, 0x0000000050000000ULL, 0x00000000A0000000ULL, 0x0000000040000000ULL,
    0x0000000200000000ULL, 0x0000000500000000ULL, 0x0000000A00000000ULL, 0x0000001400000000ULL,
    0x0000002800000000ULL, 0x0000005000000000ULL, 0x000000A000000000ULL, 0x0000004000000000ULL,
    0x0000020000000000ULL, 0x0000050000000000ULL, 0x00000A0000000000ULL, 0x0000140000000000ULL,
    0x0000280000000000ULL, 0x0000500000000000ULL, 0x0000A00000000000ULL, 0x0000400000000000ULL,
    0x0002000000000000ULL, 0x0005000000000000ULL, 0x000A000000000000ULL, 0x0014000000000000ULL,
    0x0028000000000000ULL, 0x0050000000000000ULL, 0x00A0000000000000ULL, 0x0040000000000000ULL,
    0x0200000000000000ULL, 0x0500000000000000ULL, 0x0A00000000000000ULL, 0x1400000000000000ULL,
    0x2800000000000000ULL, 0x5000000000000000ULL, 0xA000000000000000ULL, 0x4000000000000000ULL,
    0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL,
    0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL
};

// Black pawn attacks bitboards
constexpr std::array<uint64_t, 64> B_PAWN_ATTACKS = {
    0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL,
    0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL,
    0x0000000000000002ULL, 0x0000000000000005ULL, 0x000000000000000AULL, 0x0000000000000014ULL,
    0x0000000000000028ULL, 0x0000000000000050ULL, 0x00000000000000A0ULL, 0x0000000000000040ULL,
    0x0000000000000200ULL, 0x0000000000000500ULL, 0x0000000000000A00ULL, 0x0000000000001400ULL,
    0x0000000000002800ULL, 0x0000000000005000ULL, 0x000000000000A000ULL, 0x0000000000004000ULL,
    0x0000000000020000ULL, 0x0000000000050000ULL, 0x00000000000A0000ULL, 0x0000000000140000ULL,
    0x0000000000280000ULL, 0x0000000000500000ULL, 0x0000000000A00000ULL, 0x0000000000400000ULL, 
    0x0000000002000000ULL, 0x0000000005000000ULL, 0x000000000A000000ULL, 0x0000000014000000ULL,
    0x0000000028000000ULL, 0x0000000050000000ULL, 0x00000000A0000000ULL, 0x0000000040000000ULL,
    0x0000000200000000ULL, 0x0000000500000000ULL, 0x0000000A00000000ULL, 0x0000001400000000ULL,
    0x0000002800000000ULL, 0x0000005000000000ULL, 0x000000A000000000ULL, 0x0000004000000000ULL,
    0x0000020000000000ULL, 0x0000050000000000ULL, 0x00000A0000000000ULL, 0x0000140000000000ULL,
    0x0000280000000000ULL, 0x0000500000000000ULL, 0x0000A00000000000ULL, 0x0000400000000000ULL,
    0x0002000000000000ULL, 0x0005000000000000ULL, 0x000A000000000000ULL, 0x0014000000000000ULL,
    0x0028000000000000ULL, 0x0050000000000000ULL, 0x00A0000000000000ULL, 0x0040000000000000ULL
};

// Castle Masks
constexpr uint64_t E1_MASK = 0x0000000000000010ULL;
constexpr uint64_t E8_MASK = 0x1000000000000000ULL;
constexpr uint64_t A1_MASK = 0x0000000000000001ULL;
constexpr uint64_t A8_MASK = 0x0100000000000000ULL;
constexpr uint64_t H1_MASK = 0x0000000000000080ULL;
constexpr uint64_t H8_MASK = 0x8000000000000000ULL;
constexpr uint64_t F1G1_MASK = 0x0000000000000060ULL;
constexpr uint64_t C1D1_MASK = 0x000000000000000CULL;
constexpr uint64_t B1C1D1_MASK = 0x000000000000000EULL;
constexpr uint64_t B8C8D8_MASK = 0x0E00000000000000ULL;
constexpr uint64_t F8G8_MASK = 0x6000000000000000ULL;
constexpr uint64_t C8D8_MASK = 0x0C00000000000000ULL;


constexpr int MIRROR_INDEX[64] = {
    56, 57, 58, 59, 60, 61, 62, 63,
    48, 49, 50, 51, 52, 53, 54, 55,
    40, 41, 42, 43, 44, 45, 46, 47,
    32, 33, 34, 35, 36, 37, 38, 39,
    24, 25, 26, 27, 28, 29, 30, 31,
    16, 17, 18, 19, 20, 21, 22, 23,
     8,  9, 10, 11, 12, 13, 14, 15,
     0,  1,  2,  3,  4,  5,  6,  7
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

const std::array<std::string, 64> SQUARE_STRINGS = {
    "A1", "B1", "C1", "D1", "E1", "F1", "G1", "H1",
    "A2", "B2", "C2", "D2", "E2", "F2", "G2", "H2",
    "A3", "B3", "C3", "D3", "E3", "F3", "G3", "H3",
    "A4", "B4", "C4", "D4", "E4", "F4", "G4", "H4",
    "A5", "B5", "C5", "D5", "E5", "F5", "G5", "H5",
    "A6", "B6", "C6", "D6", "E6", "F6", "G6", "H6",
    "A7", "B7", "C7", "D7", "E7", "F7", "G7", "H7",
    "A8", "B8", "C8", "D8", "E8", "F8", "G8", "H8"
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

// Helper Array for pieceType to String conversion
constexpr std::array<const char*, 12> pieceNames = {
    "White Pawn", "White Knight", "White Bishop", "White Rook", "White Queen", "White King",
    "Black Pawn", "Black Knight", "Black Bishop", "Black Rook", "Black Queen", "Black King"
};

constexpr int PHASE_VALUES[12] = {
    0,  // White Pawn
    1,  // White Knight
    1,  // White Bishop
    2,  // White Rook
    4,  // White Queen
    0,  // White King
    0,  // Black Pawn
    1,  // Black Knight
    1,  // Black Bishop
    2,  // Black Rook
    4,  // Black Queen
    0   // Black King
};



constexpr int TOTAL_PHASE = 24; 


// Define indices for move type tracking
enum PerftMoveType {
    CAPTURES = 0,
    EN_PASSANT,
    CASTLES,
    PROMOTIONS,
    QUIET_MOVES,
    TOTAL_TYPES
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

inline int getLSB(uint64_t bitboard) {
    return __builtin_ctzll(bitboard); 
}

inline int popLSB(uint64_t &bitboard) {
    int index = __builtin_ctzll(bitboard); // Gets index of LSB
    bitboard &= bitboard - 1; // Removes LSB
    return index;
}

// Move codes from nibble flag
enum class MoveCode : uint8_t {
    QUIET = 0, DOUBLE_PAWN_PUSH, KING_CASTLE, QUEEN_CASTLE, CAPTURE, EN_PASSANT, 
    KNIGHT_PROMO = 8, BISHOP_PROMO, ROOK_PROMO, QUEEN_PROMO, KNIGHT_PROMO_CAPTURE, BISHOP_PROMO_CAPTURE, ROOK_PROMO_CAPTURE, QUEEN_PROMO_CAPTURE
};

const std::array<std::string, 16> MOVE_CODE_STRINGS = {
    "QUIET", "DOUBLE_PAWN_PUSH", "KING_CASTLE", "QUEEN_CASTLE", "CAPTURE", "EN_PASSANT", "CODE 6", "CODE 7?", "KNIGHT_PROMO", "BISHOP_PROMO", "ROOK_PROMO", "QUEEN_PROMO", "KNIGHT_PROMO_CAPTURE", "BISHOP_PROMO_CAPTURE", "ROOK_PROMO_CAPTURE", "QUEEN_PROMO_CAPTURE"
};

struct MoveState {
    Square prevEnPassant;   // En passant square before move
    std::array<bool, 4> prevCastleRights; // Castling rights before move
    uint8_t prevHalfmoveClock; // Halfmove clock before move
    std::optional<PieceType> capturedPiece;   // Captured piece type (std::nullopt if no capture)
};


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


constexpr std::array<uint64_t, 64> generateFrontFill() {
    std::array<uint64_t, 64> table = {};
    for (int sq = 0; sq < 64; ++sq) {
        uint64_t mask = 0ULL;
        int rank = sq / 8;
        for (int r = rank + 1; r < 8; ++r) {
            mask |= (1ULL << (sq % 8 + r * 8));  // Shift up by ranks
        }
        table[sq] = mask;
    }
    return table;
}

constexpr std::array<uint64_t, 64> generateRearFill() {
    std::array<uint64_t, 64> table = {};
    for (int sq = 0; sq < 64; ++sq) {
        uint64_t mask = 0ULL;
        int rank = sq / 8;
        for (int r = rank - 1; r >= 0; --r) {
            mask |= (1ULL << (sq % 8 + r * 8));  // Shift down by ranks
        }
        table[sq] = mask;
    }
    return table;
}

constexpr std::array<uint64_t, 64> generateFrontAttackFill(const std::array<uint64_t, 64> frontFill) {
    std::array<uint64_t, 64> table = {};
    for (int sq = 0; sq < 64; ++sq) {
        uint64_t front = frontFill[sq];
        uint64_t leftAttack = (front & ~A_FILE) >> 1; // Left diagonal attacks
        uint64_t rightAttack = (front & ~H_FILE) << 1; // Right diagonal attacks
        table[sq] = front | leftAttack | rightAttack; 
    }
    return table;
}

constexpr std::array<uint64_t, 64> generateRearAttackFill(const std::array<uint64_t, 64> rearFill) {
    std::array<uint64_t, 64> table = {};
    for (int sq = 0; sq < 64; ++sq) {
        uint64_t rear = rearFill[sq];
        uint64_t leftAttack = (rear & ~A_FILE) >> 1; // Left diagonal attacks
        uint64_t rightAttack = (rear & ~H_FILE) << 1; // Right diagonal attacks
        table[sq] = rear | leftAttack | rightAttack; 
    }
    return table;
}

constexpr std::array<uint64_t, 64> FRONT_FILL = generateFrontFill();
constexpr std::array<uint64_t, 64> REAR_FILL = generateRearFill();
constexpr std::array<uint64_t, 64> FRONT_ATTACK_FILL = generateFrontAttackFill(FRONT_FILL);
constexpr std::array<uint64_t, 64> REAR_ATTACK_FILL = generateRearAttackFill(REAR_FILL);

