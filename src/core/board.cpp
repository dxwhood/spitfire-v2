#include "board.h"


namespace chess {


Board::Board() {
    for (int i = 0; i < 12; i++) {
        bitboards[i] = 0;
    }
}

void Board::clearBoard() {
    for (int i = 0; i < 12; i++) {
        bitboards[i] = 0;
    }
}

void Board::setPieces(uint64_t bitboard, PieceType piece){
    bitboards[enumToInt(piece)] = bitboard;
}

void Board::clearPieceType(uint64_t bitboard, PieceType piece){
    bitboards[enumToInt(piece)] &= ~bitboard;
}

void Board::setDefaultPosition(){
    for(int i=0; i<12; i++){
        bitboards[i] = STARTING_POSITIONS[i];
    }
}

void Board::setDebugPosition(){
    for(int i=0; i<12; i++){
        bitboards[i] = MID_GAME_POSITIONS[i];
    }
}

void Board::setPiece(PieceType piece, Square square){
    setBit(bitboards[enumToInt(piece)], enumToInt(square));
}

void Board::clearPiece(Square square){
    // clean for loop to clear piece
    for(int i=0; i<12; i++){
        clearBit(bitboards[i], enumToInt(square));
    }
}

Color Board::getPieceColor(Square square) const{
    for(int i=0; i<12; i++){
        if(getBit(bitboards[i], enumToInt(square))){
            return (i < 6)? Color::WHITE : Color::BLACK;
        }
    }
    return Color::WHITE; // default return
}

PieceType Board::getPieceType(Square square) const{
    for(int i=0; i<12; i++){
        if(getBit(bitboards[i], enumToInt(square))){
            return static_cast<PieceType>(i);
        }
    }
    return PieceType::WHITE_PAWN; // default return
}

uint64_t Board::getAllPieces(PieceType piece) const{
    return bitboards[enumToInt(piece)];
}

uint64_t Board::getOccupancy() const{
    uint64_t board = 0;
    for(int i=0; i<12; i++){
        board |= bitboards[i];
    }
    return board;
}

uint64_t Board::getWhiteOccupancy() const{
    uint64_t board = 0;
    for(int i=0; i<6; i++){
        board |= bitboards[i];
    }
    return board;
}

uint64_t Board::getBlackOccupancy() const{
    uint64_t board = 0;
    for(int i=6; i<12; i++){
        board |= bitboards[i];
    }
    return board;
}

uint64_t Board::getEmpty() const{
    return ~getOccupancy();
}


std::array<uint64_t, 12> Board::getBitboards() const{
    return bitboards;
}



}  // namespace chess
