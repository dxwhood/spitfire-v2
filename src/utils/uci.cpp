#include "uci.h"

namespace chess{

namespace uci{

    // This function will run on a separate thread.
    void inputListener() {
        std::string input;
        while (std::getline(std::cin, input)) { // Blocks the seperate thread only
            if (input == "stop") {
                search::stopSearch.store(true);
                break;
            }
        }
    }

    void loop() {
        std::string command;

        while (true) {
            std::getline(std::cin, command);  // Read UCI command from GUI

            if (command == "uci") {
                std::cout << "id name Spitfire-v2" << std::endl;
                std::cout << "id author Damien X. Hood" << std::endl;
                std::cout << "uciok" << std::endl;
            } 
            else if (command == "isready") {
                std::cout << "readyok" << std::endl;
            } 
            else if (command.rfind("position", 0) == 0) {
                handlePosition(command);
            } 
            else if (command.rfind("go", 0) == 0) {
                handleGo(command);
            } 
            else if (command == "quit") {
                break;  
            }
        }
    }



    #include <vector>

    void handlePosition(const std::string &command) {
        std::istringstream iss(command);
        std::string token;
        iss >> token;  // Skip "position"

        std::string positionType;
        iss >> positionType;

        if (positionType == "startpos") {
            globals.board.setDefaultPosition();
        } 
        else if (positionType == "fen") {
            std::string fen;
            while (iss >> token && token != "moves") {
                fen += token + " ";
            }
            globals.board.fenToBoard(fen);
        }

        // If there are moves, play them 
        while (iss >> token) {
            if (token == "moves") continue;
            Move move = Input::parseUCIMove(globals.board, token);
            globals.board.makeMove(move);
        }
    }

    void handleGo(const std::string &command) {
        std::istringstream iss(command);
        std::string token;
        iss >> token;  // Skip "go"

        int timeWhite = -1, timeBlack = -1, movetime = -1;
        int depth = 30;
        bool infinite = false;
        
        while (iss >> token) {
            if (token == "wtime") iss >> timeWhite;
            else if (token == "btime") iss >> timeBlack;
            else if (token == "movetime") iss >> movetime;
            else if (token == "depth") iss >> depth;
            else if (token == "infinite") infinite = true;

        }


        if (movetime == -1) {
            movetime = (globals.board.getIsWhiteTurn()) ? timeWhite/40 : timeBlack/40;
        }

        // For infinite mode, spawn the listener thread.
        if (infinite) {
            search::stopSearch.store(false);
            std::thread inputThread(uci::inputListener);
            inputThread.detach();  
        }

        search::think(globals.board, 30, !infinite, movetime, true); // Perform search

        std::cout << "bestmove " << search::searchState.bestMove.toUCIString() << std::endl;
    }

}
}