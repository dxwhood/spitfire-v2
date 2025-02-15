#include "evaluation.h"
#include "heuristics.h"


namespace chess{


namespace eval{

    // formatted for negamax
    int evaluate(Board &board){
        int score = 0;
        score += heuristics::pieceValue(board);
        score += heuristics::pieceSquareTable(board);

        return board.getIsWhiteTurn()? score : -score;
    }






}
}