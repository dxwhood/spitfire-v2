#pragma once

#include "core/board.h"
#include "core/movegen.h"
#include "core/move.h"
#include "utils/display.h"
#include "utils/input.h"
#include "search/search.h"
#include <sstream>
#include <cctype>


namespace chess {

class Game {
    public:
        Game();
        void start(bool playerWhite = true, std::string fen = "", int depth = 5);
        
        Board board;

    private:
        
};

}