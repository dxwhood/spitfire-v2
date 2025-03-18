#pragma once

#include "core/definitions.h"
#include "core/board.h"
#include "core/move.h"
#include "core/movegen.h"
#include "search/search.h"
#include "eval/evaluation.h"
#include "utils/display.h"
#include "utils/input.h"
#include "eval/heuristics.h"
#include "eval/eval_constants.h"
#include <string>
#include <sstream>

namespace chess{

namespace uci{

    struct uciGlobals{
        Board board;
    };

    inline uciGlobals globals;

    void inputListener();

    void loop();
    
    void handlePosition(const std::string &command);
    void handleGo(const std::string &command);



}
}