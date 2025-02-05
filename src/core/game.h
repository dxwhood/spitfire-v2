#pragma once

#include "core/board.h"
#include "core/movegen.h"
#include "core/move.h"
#include "utils/display.h"
#include "utils/input.h"

namespace chess {

class Game {
    public:
        Game();
        void start(bool playerWhite);
        void playMove(Move move);

        // getters
        Board getBoard() const { return board; }
        bool getIsWhiteTurn() const { return isWhiteTurn; }


    private:
        Board board;
        bool isWhiteTurn;






};





}