#include "hashing.h"

namespace chess {

    TranspositionTable::TranspositionTable() {
        initZobristKeys();
    }

    void TranspositionTable::store(uint64_t hash, int depth, int score, TTFlag flag, Move bestMove) {
        table[hash] = {hash, score, depth, flag, bestMove};
    }

    bool TranspositionTable::probe(uint64_t hash, int depth, int alpha, int beta, int &score, Move &bestMove) {
        if (table.find(hash) != table.end()) {
            TTEntry &entry = table[hash];

            // Return if deep enough
            if (entry.depth >= depth) {
                if (entry.flag == EXACT) {
                    score = entry.score;
                    bestMove = entry.bestMove;
                    return true;
                }
                if (entry.flag == LOWERBOUND && entry.score >= beta) {
                    score = entry.score;
                    return true;
                }
                if (entry.flag == UPPERBOUND && entry.score <= alpha) {
                    score = entry.score;
                    return true;
                }
            }

            bestMove = entry.bestMove;
        }
        return false;
    }


    void TranspositionTable::initZobristKeys() {
        std::mt19937_64 rng(123456789); 
        std::uniform_int_distribution<uint64_t> dist;

        // Zobrist key generation
        for (int square = 0; square < 64; ++square) {
            for (int piece = 0; piece < 12; ++piece) {
                zobristTable[square][piece] = dist(rng);
            }
        }

        zobristBlackToMove = dist(rng);
    }

    uint64_t TranspositionTable::computeHash(const Board &board) {
        uint64_t hash = 0;

        for (int square = 0; square < 64; ++square) {
            std::optional<PieceType> pieceOpt = board.getPieceType(static_cast<Square>(square));
            if (pieceOpt.has_value()) {
                hash ^= zobristTable[square][enumToInt(pieceOpt.value())];
            }
        }

        if (!board.getIsWhiteTurn()) {
            hash ^= zobristBlackToMove;
        }

        return hash;
    }


}