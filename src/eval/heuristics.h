#include "core/definitions.h"
#include "core/board.h"
#include "core/movegen.h"

namespace chess{

namespace heuristics{
    
    int pieceValue(Board &board);
    int pieceSquareTable(Board &board);
    int mobility(Board &board);
    int kingSafety(Board &board);

    int pawnShield(Board &board, Color color, int phase);




}
}