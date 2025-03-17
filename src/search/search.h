#pragma once

#include "core/definitions.h"
#include "core/movegen.h"
#include "eval/evaluation.h"
#include "eval/eval_constants.h"
#include "search/hashing.h"

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
        std::optional<Move> killerMoves[50][2]; // Killer moves for each depth (up to 50)
        int historyHeuristic[64][64]; 
        TranspositionTable tt;


        void reset() {
            bestMove = Move();
            bestScore = NEG_INF;
            bestScoreThisIteration = NEG_INF;
            currentDepth = 0;
            timeLimitMs = 0;
            startTime = std::chrono::high_resolution_clock::now();
            nodeCount = 0;
            searchStopped = false;
            // Reset killerMoves for all depths and moves
            for (int d = 0; d < 50; d++) {
                for (int i = 0; i < 2; i++) {
                    killerMoves[d][i] = std::nullopt;
                }
            }
            // Reset historyHeuristic
            for (int i = 0; i < 64; i++) {
                for (int j = 0; j < 64; j++) {
                    historyHeuristic[i][j] = 0;
                }
            }
            tt = TranspositionTable();
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

    int moveScore(const Move &move, const Board &board, int depth);
    void moveOrdering(MoveList &moveList, const Board &board, int depth);

}
}
