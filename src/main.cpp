#include "utils/uci.h"
#include "core/game.h"  // Assuming startgame() is in game.h
#include <iostream>
#include <vector>
#include <string>

using namespace chess;

int main(int argc, char* argv[]) {
    bool consoleMode = false;
    bool playAsWhite = true;  // Default: engine plays as White

    // Convert command-line arguments into a vector for easy processing
    std::vector<std::string> args(argv + 1, argv + argc);

    for (const std::string& arg : args) {
        if (arg == "--console") {
            consoleMode = true;
        } else if (arg == "--black") {
            playAsWhite = false;  // Engine plays as Black
        } else if (arg == "--white") {
            playAsWhite = true;   // Engine plays as White (redundant, but allowed)
        }
    }

    if (consoleMode) {
        Game game;
        game.start(playAsWhite);
    } else {
        uci::loop();  // Start UCI mode if no arguments are given
    }

    return 0;
}
