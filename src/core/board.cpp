#include "board.h"
#include <iostream>


namespace chess {


Board::Board() {
    for (int i = 0; i < 12; i++) {
        bitboards[i] = 0;
    }
}

void Board::printBoard() const {
    std::cout << "Printing Full Board..." << std::endl;
}

void Board::printPiece(PieceType piece) const {
    int piecePos = enumToInt(piece);
    std::cout << "Printing Piece... ";
    std::cout << pieceNames[piecePos] << std::endl;

    // print board
    for(int i=8; i>0; i--){
        for (int j=8; j>0; j--){
            std::cout << getBit(bitboards[piecePos], (8*i)-j) << " ";
        }
        std::cout << std::endl;
    }

    for(int i=8; i>0; i--){
        for (int j=8; j>0; j--){
            std::cout << (8*i)-j << " ";
        }
        std::cout << std::endl;
    }
}


void Board::printBitboard(uint64_t bitboard) const{
    std::cout << "Printing Bitboard" << std::endl;
    for(int i=8; i>0; i--){
        for (int j=8; j>0; j--){
            std::cout << getBit(bitboard, (8*i)-j) << " ";
        }
        std::cout << std::endl;
    }
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

}  // namespace chess
