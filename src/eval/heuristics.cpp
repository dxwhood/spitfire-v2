#include "heuristics.h"
#include "eval_constants.h"

namespace chess{

namespace heuristics{

    int pieceValue(Board &board){
        int score = 0;
        for(int i=0; i<64; i++){
            Square square = static_cast<Square>(i);
            std::optional<PieceType> pieceOpt = board.getPieceType(square);
            if(!pieceOpt.has_value()){
                continue;
            }
            PieceType piece = pieceOpt.value();
            score += PIECE_VALUES[enumToInt(piece)];
        }

        return score;
    }

    int pieceSquareTable(Board &board){
        int mgScore = 0;
        int egScore = 0;
        for(int i=0; i<64; i++){
            Square square = static_cast<Square>(i);
            std::optional<PieceType> pieceOpt = board.getPieceType(square);
            if(!pieceOpt.has_value()){
                continue;
            }
            PieceType piece = pieceOpt.value();
            int pieceIndex = enumToInt(piece);
            if (pieceIndex < 6) {
                mgScore += PIECE_SQUARE_TABLES_MG[pieceIndex][MIRROR_INDEX[i]];
                egScore += PIECE_SQUARE_TABLES_EG[pieceIndex][i];
            } else {
                mgScore -= PIECE_SQUARE_TABLES_MG[pieceIndex][MIRROR_INDEX[i]];
                egScore -= PIECE_SQUARE_TABLES_EG[pieceIndex][i];
            }
        }
        
        int phase = board.getPhase();
        if (phase >= TOTAL_PHASE){
            phase = TOTAL_PHASE;
        }

        return ((egScore * (TOTAL_PHASE - phase)) + (mgScore * phase)) / TOTAL_PHASE;
    }



}
}