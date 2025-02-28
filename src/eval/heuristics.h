#include "core/definitions.h"
#include "core/board.h"
#include "core/movegen.h"

namespace chess{

namespace heuristics{
    
    int pieceValue(Board &board, int phase);
    int pieceSquareTable(Board &board, int phase);
    int mobility(Board &board, int phase);
    int kingSafety(Board &board, int phase);

    int pawnShield(Board &board, Color color, int phase);
    int kingExposure(Board &board, Color color, int phase);


}
}