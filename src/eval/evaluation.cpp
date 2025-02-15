#include "evaluation.h"
#include "heuristics.h"


namespace chess{


namespace eval{

    // formatted for negamax
    int evaluate(Board &board){
        int score = 0;
        uint64_t occupied = board.getOccupancy();
        for(int i=0; i<64; i++){
            if(getBit(occupied, i)){
                score += heuristics::pieceValue(board, static_cast<Square>(i));
            }
        }
        return board.getIsWhiteTurn()? score : -score;
    }






}
}