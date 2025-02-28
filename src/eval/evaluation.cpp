#include "evaluation.h"
#include "heuristics.h"


namespace chess{


namespace eval{

    // formatted for negamax
    int evaluate(Board &board, bool relative){
        int phase = board.getPhase();
        int score = 0;
        score += heuristics::pieceValue(board);
        score += heuristics::pieceSquareTable(board);
        score += heuristics::mobility(board);

        if(relative){
            return board.getIsWhiteTurn()? score : -score;
        }
        else{
            return score;
        }
    }






}
}