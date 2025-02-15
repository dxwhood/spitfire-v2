#include "core/definitions.h"
#include "core/movegen.h"
#include "eval/evaluation.h"

namespace chess{

namespace search{

    // Negamax simple search
    int negamax(Board &board, int depth, Move &bestMove); 
    int negamaxAB(Board &board, int depth, int alpha, int beta, Move &bestMove); 


}
}
