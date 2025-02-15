#include "heuristics.h"

namespace chess{

namespace heuristics{


    int pieceValue(Board &board, Square square){
        std::optional<PieceType> pieceOpt = board.getPieceType(square);
        if(!pieceOpt.has_value()){
            return 0;
        }
        PieceType piece = pieceOpt.value();
        return pieceValues[enumToInt(piece)];
    }





}
}