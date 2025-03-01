#include "heuristics.h"

namespace chess{

namespace heuristics{

    int pieceValue(Board &board, int phase){
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

    int pieceSquareTable(Board &board, int phase){
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

        return ((egScore * (TOTAL_PHASE - phase)) + (mgScore * phase)) / TOTAL_PHASE;
    }

    int mobility(Board &board, int phase){
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
        return ((whiteMobilityEG - blackMobilityEG) * (TOTAL_PHASE - phase) + (whiteMobilityMG - blackMobilityMG) * phase) / TOTAL_PHASE;
    }

    int kingSafety(Board &board, int phase){
        int score = 0;
        score += (pawnShield(board, Color::WHITE, phase) - pawnShield(board, Color::BLACK, phase));
        score += (kingExposure(board, Color::WHITE, phase) - kingExposure(board, Color::BLACK, phase));        
        return score;
    }

    int pawnStructure(Board &board, int phase){
        int score = 0;
        score += (passedPawns(board, Color::WHITE, phase) - passedPawns(board, Color::BLACK, phase));
        score += (isolatedPawns(board, Color::WHITE, phase) - isolatedPawns(board, Color::BLACK, phase));

        return score;
    }

    int pawnShield(Board &board, Color color, int phase){
        Square kingSquare = (color == Color::WHITE)? board.getKingSquare(Color::WHITE) : board.getKingSquare(Color::BLACK);
        uint64_t pawnShield = board.getBitboard(color == Color::WHITE? PieceType::WHITE_PAWN : PieceType::BLACK_PAWN) & PAWN_SHIELD_MASKS[enumToInt(kingSquare)];
        int PawnShieldScoreMG = PAWN_SHIELD_STRENGTH[__builtin_popcountll(pawnShield)];
        int PawnShieldScoreEG = 0;
        
        // Return interpolated score
        return ((PawnShieldScoreEG * (TOTAL_PHASE - phase)) + (PawnShieldScoreMG * phase)) / TOTAL_PHASE;
    }

    int kingExposure(Board &board, Color color, int phase){
        Square kingSquare = (color == Color::WHITE)? board.getKingSquare(Color::WHITE) : board.getKingSquare(Color::BLACK);
        int kingExposureScoreMG = 0;
        int kingExposureScoreEG = 0;
        File kingFile = getFile(kingSquare);

        // Check king file and adjancent file for openness
        if(board.isOpenFile(kingFile)){
            kingExposureScoreMG -= 50;
        } 
        else if(board.isSemiOpenFile(kingFile, color)){
            kingExposureScoreMG -= 25;
        }

        if(kingFile != File::A_FILE && board.isOpenFile(static_cast<File>(enumToInt(kingFile) - 1))){
            kingExposureScoreMG -= 25;
        }
        else if(kingFile != File::A_FILE && board.isSemiOpenFile(static_cast<File>(enumToInt(kingFile) - 1), color)){
            kingExposureScoreMG -= 10;
        }

        if(kingFile != File::H_FILE && board.isOpenFile(static_cast<File>(enumToInt(kingFile) + 1))){
            kingExposureScoreMG -= 25;
        }
        else if(kingFile != File::H_FILE && board.isSemiOpenFile(static_cast<File>(enumToInt(kingFile) + 1), color)){
            kingExposureScoreMG -= 10;
        }

        // check if king is castled
        if(color == Color::WHITE){
            if(board.getPieceType(Square::G1) == PieceType::WHITE_KING || board.getPieceType(Square::C1) == PieceType::WHITE_KING){
                kingExposureScoreMG += 30;
            } else{
                kingExposureScoreMG -= 30;
            }
        } else{
            if(board.getPieceType(Square::G8) == PieceType::BLACK_KING){
                kingExposureScoreMG -= 50;
            } else{
                kingExposureScoreMG -= 30;
            }
        }


        // Danger Zone
        uint64_t dangerZone = KING_DANGER_ZONE_MASKS[enumToInt(kingSquare)];
        uint64_t enemyAttacks = Movegen::colorPseudo(board, (color == Color::WHITE)? Color::BLACK : Color::WHITE);
        uint64_t enemyOccupancy = board.getOccupancy((color == Color::WHITE)? Color::BLACK : Color::WHITE);
        kingExposureScoreMG -= __builtin_popcountll(dangerZone & enemyAttacks) * 10;
        kingExposureScoreMG -= __builtin_popcountll(dangerZone & enemyOccupancy) * 5;
        
        // Return interpolated score
        return ((kingExposureScoreEG * (TOTAL_PHASE - phase)) + (kingExposureScoreMG * phase)) / TOTAL_PHASE;
    }

    int passedPawns(Board &board, Color color, int phase){
        uint64_t enemyAttackFill = board.getPawnAttackFill((color == Color::WHITE)? Color::BLACK : Color::WHITE);
        uint64_t friendlyPawns = board.getBitboard((color == Color::WHITE)? PieceType::WHITE_PAWN : PieceType::BLACK_PAWN);
        uint64_t passedPawns = friendlyPawns & ~enemyAttackFill;
        int passedPawnsScoreMG = 0;

        while (passedPawns) {
            int square = popLSB(passedPawns);             
            if (color == Color::WHITE) {
                passedPawnsScoreMG += PASSED_PAWN_BONUS_WHITE[square / 8]; 
            } else {
                passedPawnsScoreMG += PASSED_PAWN_BONUS_BLACK[(square / 8)]; 
            }
        }

        int passedPawnsScoreEG = passedPawnsScoreMG * 1.5;
        // Return interpolated score
        return ((passedPawnsScoreEG * (TOTAL_PHASE - phase)) + (passedPawnsScoreMG * phase)) / TOTAL_PHASE;
    }

    int isolatedPawns(Board &board, Color color, int phase){
        uint64_t friendlyPawns = board.getBitboard((color == Color::WHITE)? PieceType::WHITE_PAWN : PieceType::BLACK_PAWN);
        uint64_t friendlyPawnsCopy = friendlyPawns;
        uint64_t isolatedPawns = 0ULL;
        int isolatedPawnsScoreMG = 0;
        int isolatedPawnsScoreEG = 0;

        while(friendlyPawns){
            int square = popLSB(friendlyPawns);
            if((FILE_ADJACENT_MASKS[square%8] & friendlyPawnsCopy) == 0){
                isolatedPawns |= (1ULL << square);
            }
        }

        while(isolatedPawns){
            int square = popLSB(isolatedPawns);
            if(color == Color::WHITE){
                isolatedPawnsScoreMG += ISOLATED_PAWN_PENALTY_WHITE[square/8];
            } else{
                isolatedPawnsScoreMG += ISOLATED_PAWN_PENALTY_BLACK[square/8];
            }
        }

        isolatedPawnsScoreEG = isolatedPawnsScoreMG * 0.3;

        // Return interpolated score
        return ((isolatedPawnsScoreEG * (TOTAL_PHASE - phase)) + (isolatedPawnsScoreMG * phase)) / TOTAL_PHASE;
    }


}
}