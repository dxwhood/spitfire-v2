#include "core/movegen.h"  // Includes move generation logic
#include "core/board.h"
#include <iostream>
#include <bit>
#include <iostream>
#include <vector>
#include <iomanip> // for formatting output
#include "utils/display.h"

namespace{
    // From Nihar Karve - much cleaner way of implemententing hyperbola quintessence
    uint64_t hyp_quint(uint64_t pieceMask, uint64_t occ, uint64_t lineMask) {
        return (((lineMask & occ) - pieceMask * 2) ^
            reverse(reverse(lineMask & occ) - reverse(pieceMask) * 2)) & lineMask;
    }
}

namespace chess {

namespace Movegen {

    std::vector<Move> generateValidMoves(Board &board, Color color){
        std::vector<Move> allMoves;
        std::vector<Move> pseudoMoves = getPseudoMoves(board, color);
        for(Move move : pseudoMoves){
            if(isLegalMove(board, move)){
                allMoves.push_back(move);
            }
        }
        return allMoves;
    }

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
        // If castling rights are available for current color add castling moves to the list
        if (color == Color::WHITE){
            if(board.getCastlingRights()[0]){
                allMoves.push_back(Move(Square::E1, Square::G1, 0b0010));
            }
            if(board.getCastlingRights()[1]){
                allMoves.push_back(Move(Square::E1, Square::C1, 0b0011));
            }
        } else {
            if(board.getCastlingRights()[2]){
                allMoves.push_back(Move(Square::E8, Square::G8, 0b0010));
            }
            if(board.getCastlingRights()[3]){
                allMoves.push_back(Move(Square::E8, Square::C8, 0b0011));
            }
        }
        return allMoves;
    }

    uint64_t colorPseudo(const Board &board, Color color, bool attacks){
        uint64_t occupied = board.getOccupancy(color);
        uint64_t pseudo = 0ULL;
        for(int i=0; i<64; i++){
            if(getBit(occupied, i)){
                Square square = static_cast<Square>(i);
                pseudo |= pseudoLegal(board, square, attacks);
            }
        }
        return pseudo;
    }

    uint64_t pseudoLegal(const Board &board, Square square, bool attacks){
        std::optional<PieceType> pieceOpt = board.getPieceType(square);
        if(!pieceOpt.has_value()){
            return 0ULL;
        }
        PieceType piece = pieceOpt.value();
        switch(piece){
            using enum PieceType;
            case WHITE_PAWN:
            case BLACK_PAWN:
                return pawnPseudo(board, square, attacks);
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

    uint64_t pawnPseudo(const Board &board, Square square, bool attacks){
        Color color = board.getPieceColor(square);
        Rank rank = getRank(square);
        File file = getFile(square);
        uint64_t occupied_all = board.getOccupancy();
        uint64_t occupied_friendly = (color == Color::WHITE)? board.getWhiteOccupancy() : board.getBlackOccupancy();
        uint64_t occupied_foe = (color == Color::WHITE)? board.getBlackOccupancy() : board.getWhiteOccupancy();
        uint64_t captures = (color == Color::WHITE)? W_PAWN_ATTACKS[enumToInt(square)] : B_PAWN_ATTACKS[enumToInt(square)];
        uint64_t moves = 0ULL; // initialize moves

        // Double Push
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
        if (attacks){
            moves |= (captures & (~occupied_friendly));
        } else {
            moves |= (occupied_foe & captures);
        }

        // Consider en passant 
        if(board.getEnPassantSquare() != Square::A1){
            switch(color){
                using enum Color;
                case WHITE:
                    if(rank == Rank::RANK_5){
                        if(file != File::A_FILE && board.getEnPassantSquare() == static_cast<Square>(enumToInt(square) + 7)){
                            moves |= (1ULL << enumToInt(square) << 7);
                        }
                        if(file != File::H_FILE && board.getEnPassantSquare() == static_cast<Square>(enumToInt(square) + 9)){
                            moves |= (1ULL << enumToInt(square) << 9);
                        }
                    }
                    break;
                case BLACK:
                    if(rank == Rank::RANK_4){
                        if(file != File::A_FILE && board.getEnPassantSquare() == static_cast<Square>(enumToInt(square) - 9)){
                            moves |= (1ULL << enumToInt(square) >> 9);
                        }
                        if(file != File::H_FILE && board.getEnPassantSquare() == static_cast<Square>(enumToInt(square) - 7)){
                            moves |= (1ULL << enumToInt(square) >> 7);
                        }
                    }
                    break;
            }
        }

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
            if(std::abs(enumToInt(from) - enumToInt(to)) == 16){
                flags = 0b0001;
            }
        }

        // Check if a pawn is making an en passant move
        if(piece == PieceType::WHITE_PAWN || piece == PieceType::BLACK_PAWN){
            if(board.getEnPassantSquare() != Square::A1 && to == board.getEnPassantSquare()){
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
    
    bool isCheck(const Board &board, Color color){
        uint64_t king = (color == Color::WHITE)? board.getAllPieces(PieceType::WHITE_KING) : board.getAllPieces(PieceType::BLACK_KING);
        uint64_t enemyAttacks = colorPseudo(board, (color == Color::WHITE)? Color::BLACK : Color::WHITE);
        return (king & enemyAttacks) != 0;
    }

    bool isLegal(const Board &board){
        return true;
    }

    bool isLegalCastle(const Board &board, Move move){
        MoveCode code = move.getMoveCode();
        Color color = board.getPieceColor(move.getFrom());
        uint64_t attackedSquares = colorPseudo(board, (color == Color::WHITE)? Color::BLACK : Color::WHITE, true);
        uint64_t occupancy = board.getOccupancy();

        // Can't castle out of check
        if((color == Color::WHITE && (E1_MASK & attackedSquares) != 0) || (color == Color::BLACK && (E8_MASK & attackedSquares) != 0)){
            return false;
        }

        // Make sure the squares in between the king and rook are empty and not under attack
        switch (code){
            case MoveCode::KING_CASTLE:
                if(color == Color::WHITE && !((F1G1_MASK & occupancy) == 0 && (F1G1_MASK & attackedSquares) == 0)){
                    return false;
                } 
                else if(color == Color::BLACK && !((F8G8_MASK & occupancy) == 0 && (F8G8_MASK & attackedSquares) == 0)){
                    return false;
                }
                break;
            case MoveCode::QUEEN_CASTLE:
                if(color == Color::WHITE && !((B1C1D1_MASK & occupancy) == 0 && (C1D1_MASK & attackedSquares) == 0)){
                    return false;
                } 
                else if (color == Color::BLACK && !((B8C8D8_MASK & occupancy) == 0 && (C8D8_MASK & attackedSquares) == 0)){
                    return false;
                }
                break;
            default:
            
        }

        // Last check:
        // Make sure rooks are in fact in the correct position
        if(color == Color::WHITE){
            if(code == MoveCode::KING_CASTLE){
                return (board.getAllPieces(PieceType::WHITE_ROOK) & H1_MASK) != 0;
            } else {
                return (board.getAllPieces(PieceType::WHITE_ROOK) & A1_MASK) != 0;
            }
        } else {
            if(code == MoveCode::KING_CASTLE){
                return (board.getAllPieces(PieceType::BLACK_ROOK) & H8_MASK) != 0;
            } else {
                return (board.getAllPieces(PieceType::BLACK_ROOK) & A8_MASK) != 0;
            }
        }

    }

    bool isLegalMove(Board &board, Move move){
        // Check for castling
        if(move.getMoveCode() == MoveCode::KING_CASTLE || move.getMoveCode() == MoveCode::QUEEN_CASTLE){
            if (!isLegalCastle(board, move)){
                return false;
            }
        }

        Color colorTurn = board.getIsWhiteTurn()? Color::WHITE : Color::BLACK;
        board.makeMove(move);
        bool isLegal = !isCheck(board, colorTurn);
        board.unmakeMove(move);

        return isLegal;
    }


    uint64_t perft(Board &board, int depth){
        if(depth == 0){
            return 1;
        }
        uint64_t nodes = 0;
        std::vector<Move> moves = generateValidMoves(board, board.getIsWhiteTurn()? Color::WHITE : Color::BLACK);
        for(Move move : moves){
            board.makeMove(move);
            nodes += perft(board, depth - 1);
            board.unmakeMove(move);
        }
        return nodes;
    }


    uint64_t perftDivide(Board &board, int depth) {
        if (depth == 0) {
            return 1;
        }

        std::vector<Move> moves = generateValidMoves(board, board.getIsWhiteTurn() ? Color::WHITE : Color::BLACK);
        
        uint64_t totalNodes = 0;
        std::vector<std::pair<Move, uint64_t>> moveCounts; // Store each move and its perft count

        for (const Move &move : moves) {
            board.makeMove(move);
            uint64_t moveNodes = perft(board, depth - 1);
            board.unmakeMove(move);
            
            moveCounts.push_back({move, moveNodes}); // Store move and its count
            totalNodes += moveNodes;
        }

        // Print the results
        std::cout << "Perft divide at depth " << depth << ":\n";
        for (const auto &[move, count] : moveCounts) {
            std::cout << move.toUCIString() << ": " << count << std::endl;
        }
        std::cout << "Total nodes: " << totalNodes << std::endl;

        return totalNodes;
    }


    uint64_t perftDivideByType(Board &board, int depth, std::array<uint64_t, TOTAL_TYPES> &moveCounts) {
        if (depth == 0) {
            return 1;
        }

        std::vector<Move> moves = generateValidMoves(board, board.getIsWhiteTurn() ? Color::WHITE : Color::BLACK);

        uint64_t totalNodes = 0;
        for (const Move &move : moves) {
            bool atDepth1 = (depth == 1);  // Only count move types at depth 1

            // Classify move type **only at depth 1**
            if (atDepth1) {
                MoveCode code = move.getMoveCode();
                if (code == MoveCode::CAPTURE) {
                    moveCounts[CAPTURES]++;
                } else if (code == MoveCode::EN_PASSANT) {
                    moveCounts[EN_PASSANT]++;
                    moveCounts[CAPTURES]++;
                } else if (code == MoveCode::KING_CASTLE || code == MoveCode::QUEEN_CASTLE) {
                    moveCounts[CASTLES]++;
                } else if (code == MoveCode::KNIGHT_PROMO || code == MoveCode::KNIGHT_PROMO_CAPTURE ||
                        code == MoveCode::BISHOP_PROMO || code == MoveCode::BISHOP_PROMO_CAPTURE ||
                        code == MoveCode::ROOK_PROMO || code == MoveCode::ROOK_PROMO_CAPTURE ||
                        code == MoveCode::QUEEN_PROMO || code == MoveCode::QUEEN_PROMO_CAPTURE) {
                    moveCounts[PROMOTIONS]++;
                } else {
                    moveCounts[QUIET_MOVES]++;
                }
            }

            board.makeMove(move);
            uint64_t moveNodes = perftDivideByType(board, depth - 1, moveCounts);  // Recurse
            board.unmakeMove(move);

            totalNodes += moveNodes;
        }

        return totalNodes;
    }


    // Overloaded function to call
    void perftDivideByType(Board &board, int depth) {
        std::array<uint64_t, TOTAL_TYPES> moveCounts = {0, 0, 0, 0, 0}; // Initialize counts

        uint64_t totalNodes = perftDivideByType(board, depth, moveCounts);

        // Print results
        std::cout << "Perft results by move type at depth " << depth << ":\n";
        std::cout << "  Total Nodes: " << totalNodes << "\n";
        std::cout << "  Captures: " << moveCounts[CAPTURES] << "\n";
        std::cout << "  En Passant: " << moveCounts[EN_PASSANT] << "\n";
        std::cout << "  Castles: " << moveCounts[CASTLES] << "\n";
        std::cout << "  Promotions: " << moveCounts[PROMOTIONS] << "\n";
        std::cout << "  Quiet Moves: " << moveCounts[QUIET_MOVES] << "\n";
    }





}

}