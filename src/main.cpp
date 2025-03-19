#include "core/board.h"
#include "core/movegen.h"
#include "core/game.h"
#include "utils/display.h"
#include "utils/input.h"
#include "eval/evaluation.h"
#include "search/search.h"
#include "../tests/test_movegen.h"
#include <iostream>
#include <string>
#include "eval/heuristics.h"
#include "eval/eval_constants.h"
#include "utils/uci.h"


using namespace chess;



int main() {
    uci::loop();

    return 0;
}