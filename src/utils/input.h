#include <iostream>
#include <thread>
#include <chrono>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include <cctype>
#include "core/move.h"

namespace chess{

namespace Input{

    std::string inputMove();
    bool validateInputMove(std::string move);
    Move parseUCIMove(std::string move);

}

}