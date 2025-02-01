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
    
    board.printBitboard(chess::Moves::kingPseudo(board, Square::A1, Color::WHITE));

    return 0;
}