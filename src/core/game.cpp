#include "game.h"

namespace chess {


Game::Game() {
    board.setDefaultPosition();
}

void Game::start(bool playerWhite) {
    Move parsedMove;
    Move prevMove;
    Display::printBoard(board);
    bool loop = true;

    // Rewrite of the game loop
    while(true){
        if(board.getIsWhiteTurn() == playerWhite){
            std::vector<Move> playerMoves = Movegen::generateValidMoves(board, playerWhite? Color::WHITE : Color::BLACK);
            if (playerMoves.size() == 0) {
                // check for stalemate by checking if in check
                if (Movegen::isCheck(board, playerWhite? Color::WHITE : Color::BLACK)) {
                    std::cout << "Checkmate! You win!" << std::endl;
                } else {
                    std::cout << "Stalemate! It's a draw!" << std::endl;
                }
                // exit the game loop
                loop = false;
                break;
            }

            parsedMove = Input::parseUCIMove(board, Input::inputMove());
            while(std::find(playerMoves.begin(), playerMoves.end(), parsedMove) == playerMoves.end()){
                std::cout << "Illegal move. Please try again." << std::endl;
                std::cout << parsedMove << std::endl;
                parsedMove = Input::parseUCIMove(board, Input::inputMove());
            }
            board.makeMove(parsedMove);
            prevMove = parsedMove;
        } else {
            std::vector<Move> engineMoves = Movegen::generateValidMoves(board, playerWhite? Color::BLACK : Color::WHITE);
            if(engineMoves.size() == 0){
                // check for stalemate by checking if in check
                if(Movegen::isCheck(board, Color::BLACK)){
                    std::cout << "Checkmate! You win!" << std::endl;
                } else {
                    std::cout << "Stalemate! It's a draw!" << std::endl;
                }
                // exit the game loop
                loop = false;
                break;
            }

            // Random move for now
            Move engineMove = engineMoves[rand() % engineMoves.size()];
            board.makeMove(engineMove);
            // print engine move
            std::cout << "Engine move: " << engineMove.toUCIString() << std::endl;

            prevMove = engineMove;
        }

        if (loop) {
            Display::printBoard(board, prevMove);
        }
    }


}

    


}






