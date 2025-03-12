#include "test_movegen.h"

namespace chess{
namespace tests{
namespace movegen{


    void perft_test(int depth, bool speed){
        // print expected and results for perft up to 5
        Board board;
        board.setDefaultPosition();
        std::cout << "Perft Test:" << std::endl;
        std::array<std::string, 6> expected_1 = {"20", "400", "8902", "197281", "4865609","119060324"};
        std::array<std::string, 6> expected_2 = {"48", "2039", "97862", "4085603", "193690690", "8031647685"};
        std::array<std::string, 6> expected_3 = {"14", "191", "2812", "43238", "674624", "11030083"};
        std::array<std::string, 6> expected_4 = {"6", "264", "9467", "422333", "15833292", "706045033"};
        std::array<std::string, 6> expected_5 = {"44", "1486", "62379", "2103487", "89941194", "3173248218"};
        std::array<std::string, 6> expected_6 = {"46", "2079", "89890", "3894594", "164075551", "6923051137"};
        std::array<std::array<std::string, 6>, 6> expected = {expected_1, expected_2, expected_3, expected_4, expected_5, expected_6};
        std::array<std::string, 6> pgns = {"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
                                          "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -",
                                           "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - ", 
                                           "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1",
                                           "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8 ",
                                           "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10"
                                           };
        
        
        
        std::array<std::string, 6> results;

        for(int pos=0; pos <= 5; pos++){
            std::cout << "Position " << pos+1 << ":" << std::endl;
            board.fenToBoard(pgns[pos]);

            for(int i=1; i<=depth; i++){
                uint64_t nodes = Movegen::perft(board, i);
                std::cout << "Depth " << i << ": " << nodes << " nodes  |  Expected: " << expected[pos][i-1] << std::endl;
                results[i-1] = std::to_string(nodes);
            }
            std::cout << std::endl;


        // check if results match expected
            for(int i=0; i<depth; i++){
                if(results[i] != expected[pos][i]){
                    std::cout << "Perft Test Failed!" << std::endl;
                    return;
                }
            }

        }
        std::cout << "Perft Test Passed!" << std::endl;

        // Print node per second 
        board.fenToBoard(pgns[0]);
        //start timer
        auto start = std::chrono::high_resolution_clock::now();
        int nodes_1 = Movegen::perft(board, 5);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed1 = end - start;


        board.fenToBoard(pgns[1]);
        start = std::chrono::high_resolution_clock::now();
        int nodes_2 = Movegen::perft(board, 5);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed2 = end - start;
        
        std::string nps = std::to_string(static_cast<int>(((nodes_1 / elapsed1.count()) + (nodes_2 / elapsed2.count()))/2));
        std::string nps_formatted;
        if(nps.length() > 9){
            nps_formatted = nps.substr(0, nps.length()-9) + "." + nps.substr(nps.length()-7, nps.length()-8) + "B";
        } else if(nps.length() > 6){
            nps_formatted = nps.substr(0, nps.length()-6) + "." + nps.substr(nps.length()-4, nps.length()-5) + "M";
        } else if(nps.length() > 3){
            nps_formatted = nps.substr(0, nps.length()-3) + "." + nps.substr(nps.length()-1, nps.length()-2) + "K";
        } else {
            nps_formatted = nps;
        }

        std::cout << nps_formatted << " nps" << std::endl;


    }   


}
}
}