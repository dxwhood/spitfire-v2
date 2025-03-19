#include "game.h"


namespace chess {


Game::Game() {
    board.setDefaultPosition();
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Game::start(bool playerWhite, std::string fen, int thinkTime) {
    // Set FEN if provided.
    if (!fen.empty()) {
        board.fenToBoard(fen);
    } else {
        board.setDefaultPosition();
    }
    
    bool useTimeControl = true;
    Move parsedMove;
    Move prevMove;
    
    // Initial board display before any moves.
    clearScreen();
    Display::printBoard(board);
    
    while (true) {
        clearScreen();
        Display::printBoard(board, prevMove);
        
        if (board.getIsWhiteTurn() == playerWhite) {
            // Player's turn.
            MoveList playerMoveList = Movegen::generateValidMoves(board, playerWhite ? Color::WHITE : Color::BLACK);
            if (playerMoveList.count == 0) {
                // Check for checkmate or stalemate.
                if (Movegen::isCheck(board, playerWhite ? Color::WHITE : Color::BLACK)) {
                    std::cout << "Checkmate! You win!" << std::endl;
                } else {
                    std::cout << "Stalemate! It's a draw!" << std::endl;
                }
                break;  // Exit game loop.
            }
            
            // Build a vector of legal moves for easy checking.
            std::vector<Move> playerMoves;
            for (int i = 0; i < playerMoveList.count; i++) {
                playerMoves.push_back(playerMoveList.moves[i]);
            }
            
            parsedMove = Input::parseUCIMove(board, Input::inputMove());
            // If move is illegal, prompt again.
            while (std::find(playerMoves.begin(), playerMoves.end(), parsedMove) == playerMoves.end()) {
                std::cout << "Illegal move. Please try again." << std::endl;
                parsedMove = Input::parseUCIMove(board, Input::inputMove());
            }
            
            board.makeMove(parsedMove);
            prevMove = parsedMove;
        } else {
            // Engine's turn.
            MoveList engineMoveList = Movegen::generateValidMoves(board, playerWhite ? Color::BLACK : Color::WHITE);
            if (engineMoveList.count == 0) {
                if (Movegen::isCheck(board, playerWhite ? Color::BLACK : Color::WHITE)) {
                    std::cout << "Checkmate! You win!" << std::endl;
                } else {
                    std::cout << "Stalemate! It's a draw!" << std::endl;
                }
                break;  // Exit game loop.
            }
            
            search::think(board, 30, useTimeControl, 2000);
            board.makeMove(search::searchState.bestMove);
            std::cout << "Engine move: " << search::searchState.bestMove 
                      << "  Evaluation: " << eval::evaluate(board) << std::endl;
            prevMove = search::searchState.bestMove;
        }
    }
}


}






