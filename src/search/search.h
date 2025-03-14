#pragma once

#include "core/definitions.h"
#include "core/movegen.h"
#include "eval/evaluation.h"

namespace chess{

namespace search{

    constexpr int TIME_CHECK_INTERVAL = 100000; // Check time every 5000 nodes

    struct SearchState {
        Move bestMove;
        int bestScore = NEG_INF;
        int bestScoreThisIteration = NEG_INF;
        int currentDepth = 0;
        int timeLeft = 150000;
        int timeLimitMs = 0;
        std::chrono::high_resolution_clock::time_point startTime;
        int nodeCount = 0;
        bool searchStopped = false;
    };

    // Global instance of search state
    inline SearchState searchState;

    void think(Board &board, int depth, bool useTimeControl, int timeLimitMs);
    void think(Board &board, int depth); // no time control

    // Negamax simple search
    int negamax(Board &board, int depth, Move &bestMove); 
    int negamaxAB(Board &board, int depth, int alpha, int beta, Move &bestMove, bool useTimeControl = false); 
    int negamaxAB(Board &board, int depth, int alpha, int beta, Move &bestMove, int level);

}
}
