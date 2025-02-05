#include "core/movegen.h"  // Includes move generation logic
#include "core/board.h"
#include <iostream>
#include <bit>

namespace{
    // From Nihar Karve - much cleaner way of implemententing hyperbola quintessence
    uint64_t hyp_quint(uint64_t pieceMask, uint64_t occ, uint64_t lineMask) {
        return (((lineMask & occ) - pieceMask * 2) ^
            reverse(reverse(lineMask & occ) - reverse(pieceMask) * 2)) & lineMask;
    }
}

namespace chess {

namespace Movegen {

    std::vector<Move> getPseudoMoves(const Board &board, Color color){
        uint64_t occupied = board.getOccupancy(color);
        std::vector<Move> allMoves;
        for(int i=0; i<64; i++){
            if(getBit(occupied, i)){
                Square square = static_cast<Square>(i);
                std::optional<PieceType> pieceOpt = board.getPieceType(square);
                if(!pieceOpt.has_value()){
                    continue;
                }
                PieceType piece = pieceOpt.value();
                uint64_t pseudo = pseudoLegal(board, square);
                std::vector<Move> moves = bitboardToMoves(board, piece, square, pseudo);
                allMoves.insert(allMoves.end(), moves.begin(), moves.end());
            }
        }
        return allMoves;
    }

    uint64_t pseudoLegal(const Board &board, Square square){
        std::optional<PieceType> pieceOpt = board.getPieceType(square);
        if(!pieceOpt.has_value()){
            return 0ULL;
        }
        PieceType piece = pieceOpt.value();
        switch(piece){
            using enum PieceType;
            case WHITE_PAWN:
            case BLACK_PAWN:
                return pawnPseudo(board, square);
            case WHITE_KNIGHT:
            case BLACK_KNIGHT:
                return knightPseudo(board, square);
            case WHITE_BISHOP:
            case BLACK_BISHOP:
                return bishopPseudo(board, square);
            case WHITE_ROOK:
            case BLACK_ROOK:
                return rookPseudo(board, square);
            case WHITE_QUEEN:
            case BLACK_QUEEN:
                return queenPseudo(board, square);
            case WHITE_KING:
            case BLACK_KING:
                return kingPseudo(board, square);
            default:
                return 0ULL;
        }
    }

    uint64_t kingPseudo(const Board &board, Square square){

        Color color = board.getPieceColor(square);
        uint64_t kingMask = KING_MOVES[enumToInt(square)];
        uint64_t occupancy = (color == Color::WHITE)? board.getWhiteOccupancy() : board.getBlackOccupancy();
        return kingMask & ~occupancy;
    }

    uint64_t knightPseudo(const Board &board, Square square){
        Color color = board.getPieceColor(square);
        uint64_t knightMask = KNIGHT_MOVES[enumToInt(square)];
        uint64_t occupancy = (color == Color::WHITE)? board.getWhiteOccupancy() : board.getBlackOccupancy();
        return knightMask & ~occupancy;
    }

    uint64_t pawnPseudo(const Board &board, Square square){
        Color color = board.getPieceColor(square);
        Rank rank = getRank(square);
        File file = getFile(square);
        uint64_t occupied_all = board.getOccupancy();
        uint64_t occupied_foe = (color == Color::WHITE)? board.getBlackOccupancy() : board.getWhiteOccupancy();
        uint64_t captures = (color == Color::WHITE)? W_PAWN_ATTACKS[enumToInt(square)] : B_PAWN_ATTACKS[enumToInt(square)];
        uint64_t moves = 0ULL; // initialize moves

        switch (color){
            using enum Color;
            case WHITE:
                moves |= (1ULL << enumToInt(square) << 8);
                if(rank == Rank::RANK_2 && !getBit(occupied_all, enumToInt(square) + 8)){
                    moves |= (moves << 8);
                }
                break;
                
            case BLACK:
                moves |= (1ULL << enumToInt(square) >> 8);
                if(rank == Rank::RANK_7  && !getBit(occupied_all, enumToInt(square) - 8)){
                    moves |= (moves >> 8);
                }
                break;
        }

        moves &= ~occupied_all;
        moves |= (occupied_foe & captures);

        return moves;
    }

    uint64_t rookPseudo(const Board &board, Square square){
        Color color = board.getPieceColor(square);
        File file = getFile(square);
        Rank rank = getRank(square);
        uint64_t occupied = board.getOccupancy();
        uint64_t friendlyOccupied = (color == Color::WHITE)? board.getWhiteOccupancy() : board.getBlackOccupancy();

        return (hyp_quint(SQUARE_MASKS[enumToInt(square)], occupied, RANK_MASKS[enumToInt(rank)]) |
               hyp_quint(SQUARE_MASKS[enumToInt(square)], occupied, FILE_MASKS[enumToInt(file)])) & ~friendlyOccupied;

    }

    uint64_t bishopPseudo(const Board &board, Square square){
        Color color = board.getPieceColor(square);
        uint64_t occupied = board.getOccupancy();
        uint64_t friendlyOccupied = (color == Color::WHITE)? board.getWhiteOccupancy() : board.getBlackOccupancy();

        return (hyp_quint(SQUARE_MASKS[enumToInt(square)], occupied, DIAGONAL_MASKS[enumToInt(square)]) | 
             hyp_quint(SQUARE_MASKS[enumToInt(square)], occupied, ANTIDIAGONAL_MASKS[enumToInt(square)])) & ~friendlyOccupied;
    }

    uint64_t queenPseudo(const Board &board, Square square){
        return bishopPseudo(board, square) | rookPseudo(board, square);
    }

    std::vector<Move> bitboardToMoves(const Board &board, PieceType piece, Square square, const uint64_t& bitboard){
        std::vector<Move> moves;
        for(int i=0; i<64; i++){
            if(getBit(bitboard, i)){
                if(piece == PieceType::WHITE_PAWN && getRank(square) == Rank::RANK_7){ // White pawn promotion
                    moves.push_back(buildMove(board, piece, square, static_cast<Square>(i), PieceType::WHITE_QUEEN));
                    moves.push_back(buildMove(board, piece, square, static_cast<Square>(i), PieceType::WHITE_ROOK));
                    moves.push_back(buildMove(board, piece, square, static_cast<Square>(i), PieceType::WHITE_BISHOP));
                    moves.push_back(buildMove(board, piece, square, static_cast<Square>(i), PieceType::WHITE_KNIGHT));
                } else if(piece == PieceType::BLACK_PAWN && getRank(square) == Rank::RANK_2){ // Black pawn promotion
                    moves.push_back(buildMove(board, piece, square, static_cast<Square>(i), PieceType::BLACK_QUEEN));
                    moves.push_back(buildMove(board, piece, square, static_cast<Square>(i), PieceType::BLACK_ROOK));
                    moves.push_back(buildMove(board, piece, square, static_cast<Square>(i), PieceType::BLACK_BISHOP));
                    moves.push_back(buildMove(board, piece, square, static_cast<Square>(i), PieceType::BLACK_KNIGHT));
                } else {
                    moves.push_back(buildMove(board, piece, square, static_cast<Square>(i), std::nullopt)); // Normal move
                }
            }
        }
        return moves;
    }

    Move buildMove(const Board &board, PieceType piece, Square from, Square to, std::optional<PieceType> promotion){
        uint8_t flags = 0;
        // Check if a piece is captured
        std::optional<PieceType> captured = board.getPieceType(to);
        if(captured.has_value()){
            flags |= 0b0100;
        }
        // Check if a pawn is promoted
        if(promotion.has_value()){
            flags |= 0b1000;
            switch(promotion.value()){
                using enum PieceType;
                case WHITE_BISHOP: 
                case BLACK_BISHOP:
                    flags |= 0b0001; break;
                case WHITE_ROOK:
                case BLACK_ROOK: 
                    flags |= 0b0010; break;
                case WHITE_QUEEN: 
                case BLACK_QUEEN: 
                    flags |= 0b0011; break;
                default: break;
            }
        }

        // Check if a pawn is making a double push
        if((piece == PieceType::WHITE_PAWN || piece == PieceType::BLACK_PAWN) && !promotion.has_value()){
            // Check if going to en passant square
            if(to == board.getEnPassantSquare()){
                flags = 0b0101;
            }
        }

        // Check if a pawn is making an en passant move
        if(piece == PieceType::WHITE_PAWN || piece == PieceType::BLACK_PAWN){
            if(board.getPieceType(to).has_value() && board.getPieceType(to).value() == PieceType::WHITE_PAWN){
                flags = 0b0101;
            }
        }

        // check if castling
        if(piece == PieceType::WHITE_KING || piece == PieceType::BLACK_KING){
            if(from == Square::E1 && to == Square::G1){
                flags = 0b0010;
            } else if(from == Square::E1 && to == Square::C1){
                flags = 0b0011;
            } else if(from == Square::E8 && to == Square::G8){
                flags = 0b0010;
            } else if(from == Square::E8 && to == Square::C8){
                flags = 0b0011;
            }
        }
      
        return Move(from, to, flags);
    }
    

    
}

}