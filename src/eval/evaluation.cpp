#include "evaluation.h"



namespace chess{


namespace eval{

    // formatted for negamax
    int evaluate(Board &board){
        int score = 0;
        uint64_t occupied = board.getOccupancy();
        for(int i=0; i<64; i++){
            if(getBit(occupied, i)){
                score += pieceValue(board, static_cast<Square>(i));
            }
        }
        return board.getIsWhiteTurn()? score : -score;
    }


    int pieceValue(Board &board, Square square){
        std::optional<PieceType> pieceOpt = board.getPieceType(square);
        if(!pieceOpt.has_value()){
            return 0;
        }
        PieceType piece = pieceOpt.value();
        switch(piece){
            using enum PieceType;
            case WHITE_PAWN:
                return 100;
            case BLACK_PAWN:
                return -100;
            case WHITE_KNIGHT:
                return 320;
            case BLACK_KNIGHT:
                return -320;
            case WHITE_BISHOP:
                return 330;
            case BLACK_BISHOP:
                return -330;
            case WHITE_ROOK:
                return 500;
            case BLACK_ROOK:
                return -500;
            case WHITE_QUEEN:
                return 900;
            case BLACK_QUEEN:
                return -900;
            case WHITE_KING:
                return 20000;
            case BLACK_KING:
                return -20000;
            default:
                return 0;
        }
    }



}
}