#include <iostream>
#include "core/board.h"
#include "core/moves.h"

using namespace chess;


int main() {
    std::cout << "Spitfire Chess Engine Started!" << std::endl;
    chess::Board board;
    board.printBoard();
    board.printPiece(chess::PieceType::WHITE_PAWN);
    std::cout<<std::endl;
    
    for (int i=0; i<64; i++){
        board.printBitboard(KNIGHT_MOVES[i]);
    }

    return 0;
}