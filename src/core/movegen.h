#pragma once

#include <cstdint>  // Standard integer types
#include <array>
#include "core/board.h"
#include "core/move.h"
#include <vector>


// Reverse bits of a uint64_t
constexpr uint64_t reverse(uint64_t b) {
    b = (b & 0x5555555555555555) << 1 | ((b >> 1) & 0x5555555555555555);
    b = (b & 0x3333333333333333) << 2 | ((b >> 2) & 0x3333333333333333);
    b = (b & 0x0f0f0f0f0f0f0f0f) << 4 | ((b >> 4) & 0x0f0f0f0f0f0f0f0f);
    b = (b & 0x00ff00ff00ff00ff) << 8 | ((b >> 8) & 0x00ff00ff00ff00ff);

    return (b << 48) | ((b & 0xffff0000) << 16) | ((b >> 16) & 0xffff0000) | (b >> 48);
}

namespace chess {

namespace Movegen{
    
    MoveList generateValidMoves(Board &board, Color color);

    MoveList getPseudoMoves(const Board &board, Color color);

    uint64_t colorPseudo(const Board &board, Color color, bool attacks = false);

    uint64_t pseudoLegal(const Board &board, Square square, bool attacks = false);

    uint64_t kingPseudo(const Board &board, Square square);
    uint64_t knightPseudo(const Board &board, Square square);
    uint64_t pawnPseudo(const Board &board, Square square, bool attacks = false);
    uint64_t rookPseudo(const Board &board, Square square);
    uint64_t queenPseudo(const Board &board, Square square);
    uint64_t bishopPseudo(const Board &board, Square square);

    MoveList bitboardToMoves(const Board &board, PieceType piece, Square square, uint64_t& bitboard);
    Move buildMove(const Board &board, PieceType piece, Square from, Square to, std::optional<PieceType> promotion = std::nullopt);

    bool isLegal(const Board &board);
    bool isLegalMove(Board &board, Move move);
    bool isLegalCastle(const Board &board, Move move);

    bool isCheck(const Board &board, Color color); // Check if a color is in check

    

    uint64_t perft(Board &board, int depth);

    uint64_t perftDivide(Board &board, int depth);
    uint64_t perftDivideByType(Board &board, int depth, std::array<uint64_t, TOTAL_TYPES> &moveCounts);
    void perftDivideByType(Board &board, int depth);



};








}
