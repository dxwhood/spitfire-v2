#pragma once

#include "core/definitions.h"
#include "core/movegen.h"
#include "eval/evaluation.h"

namespace chess{

namespace search{

    constexpr int TIME_CHECK_INTERVAL = 100000; // Check time every 5000 nodes

    struct SearchState {
        Move bestMove = Move();
        int bestScore = NEG_INF;
        int bestScoreThisIteration = NEG_INF;
        int currentDepth = 0;
        int timeLeft = 300000;
        int timeLimitMs = 0;
        std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
        int nodeCount = 0;
        bool searchStopped = false;

        void reset() {
            bestMove = Move();
            bestScore = NEG_INF;
            bestScoreThisIteration = NEG_INF;
            currentDepth = 0;
            timeLimitMs = 0;
            startTime = std::chrono::high_resolution_clock::now();
            nodeCount = 0;
            searchStopped = false;
        }
    };

    // Global instance of search state
    inline SearchState searchState;

    void think(Board &board, int depth, bool useTimeControl, int timeLimitMs);
    void think(Board &board, int depth); // no time control

    int negamaxAB(Board &board, int depth, int alpha, int beta, Move &bestMove, bool useTimeControl = false); 
    int quiescence(Board &board, int alpha, int beta, bool useTimeControl) ;

    // Negamax simple search
    int negamax(Board &board, int depth, Move &bestMove); 
    int negamaxAB(Board &board, int depth, int alpha, int beta, Move &bestMove, int level);

}
}
