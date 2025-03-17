#pragma once

#include <unordered_map>
#include "core/movegen.h"
#include <random>

namespace chess {

enum TTFlag { EXACT, LOWERBOUND, UPPERBOUND };

struct TTEntry {
    uint64_t hash;  
    int score;
    int depth;
    TTFlag flag;
    Move bestMove;
};

class TranspositionTable {
private:
    std::unordered_map<uint64_t, TTEntry> table;
    uint64_t zobristTable[64][12]; // 64 squares × 12 piece types
    uint64_t zobristBlackToMove;
    
    void initZobristKeys();

public:
    TranspositionTable();

    void store(uint64_t hash, int depth, int score, TTFlag flag, Move bestMove);

    bool probe(uint64_t hash, int depth, int alpha, int beta, int &score, Move &bestMove);

    uint64_t computeHash(const Board &board);
};


}