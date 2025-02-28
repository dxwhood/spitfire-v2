#include "evaluation.h"
#include "heuristics.h"


namespace chess{


namespace eval{

    // formatted for negamax
    int evaluate(Board &board, bool relative){
        int phase = board.getPhase();
        int score = 0;
        score += heuristics::pieceValue(board, phase);
        score += heuristics::pieceSquareTable(board, phase);
        score += heuristics::mobility(board, phase);
        score += heuristics::kingSafety(board, phase);

        if(relative){
            return board.getIsWhiteTurn()? score : -score;
        }
        else{
            return score;
        }
    }






}
}