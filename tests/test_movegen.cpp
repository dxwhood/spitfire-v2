#include "test_movegen.h"

namespace chess{
namespace tests{
namespace movegen{


    void perft_test(){
        // print expected and results for perft up to 5
        Board board;
        board.setDefaultPosition();
        std::cout << "Perft Test:" << std::endl;
        std::array<std::string, 6> expected = {"20", "400", "8902", "197281", "4865609"};
        std::array<std::string, 6> results;
        for(int i=1; i<=5; i++){
            uint64_t nodes = Movegen::perft(board, i);
            std::cout << "Depth " << i << ": " << nodes << " nodes  |  Expected: " << expected[i-1] << std::endl;
            results[i-1] = std::to_string(nodes);
        }

        // check if results match expected
        for(int i=0; i<5; i++){
            if(results[i] != expected[i]){
                std::cout << "Perft Test Failed!" << std::endl;
                return;
            }
        }
        std::cout << "Perft Test Passed!" << std::endl;
    }


}
}
}