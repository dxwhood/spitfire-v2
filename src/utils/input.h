#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include <cctype>
#include "core/board.h"

namespace chess{

namespace Input{

    std::string inputMove();
    bool validateInputMove(const std::string& moveString);
    Move parseUCIMove(const Board& board, const std::string& moveString);

}

}