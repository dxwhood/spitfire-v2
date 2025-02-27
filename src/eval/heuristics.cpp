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

    int mobility(Board &board){
        int whiteMobilityMG = 0;
        int blackMobilityMG = 0;
        int whiteMobilityEG = 0;
        int blackMobilityEG = 0;

        for (int i = 0; i < 64; i++){
            Square square = static_cast<Square>(i);
            std::optional<PieceType> pieceOpt = board.getPieceType(square);
            if (!pieceOpt.has_value() || pieceOpt.value() == PieceType::WHITE_PAWN || pieceOpt.value() == PieceType::BLACK_PAWN){
                continue;
            }
            PieceType piece = pieceOpt.value();
            int pieceIndex = enumToInt(piece);
            if (pieceIndex < 6){
                whiteMobilityMG += MOBILITY_TABLES_MG[pieceIndex][__builtin_popcountll(Movegen::pseudoLegal(board, square, true))];
                whiteMobilityEG += MOBILITY_TABLES_EG[pieceIndex][__builtin_popcountll(Movegen::pseudoLegal(board, square, false))];
            } else{
                blackMobilityMG += MOBILITY_TABLES_MG[pieceIndex][__builtin_popcountll(Movegen::pseudoLegal(board, square, true))];
                blackMobilityEG += MOBILITY_TABLES_EG[pieceIndex][__builtin_popcountll(Movegen::pseudoLegal(board, square, false))];
            }

        }

        // Return phase interpolation of the mobility scores
        return ((whiteMobilityEG - blackMobilityEG) * (TOTAL_PHASE - board.getPhase()) + (whiteMobilityMG - blackMobilityMG) * board.getPhase()) / TOTAL_PHASE;
    }

}
}