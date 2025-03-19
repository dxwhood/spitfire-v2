#include "display.h"


namespace chess{

namespace Display{

    void printBoard(const Board &board){
        printBoard(board, Square::A1, false);
    }

    void printBoard(const Board &board, std::optional<Move> prevMove){
        printBoard(board, Square::A1, false, prevMove);
    }   


    // Overloaded function with highlighting.
    // highlightSquare: Square enum value for the piece to highlight.
    // movesBitboard: Bitboard of possible moves (attacks) to highlight.
    // highlight: If false, ignores highlightSquare and movesBitboard (used for overload simplicity).
    void printBoard(const Board &board, Square highlightSquare, bool highlight, std::optional <Move> prevMove){ 
        Square from = prevMove.has_value() ? prevMove.value().getFrom() : Square::A1;
        Square to = prevMove.has_value() ? prevMove.value().getTo() : Square::A1;
        
        std::cout << std::endl;

        std::array<uint64_t, 12> bitboards = board.getBitboards();
        uint64_t movesBitboard = Movegen::pseudoLegal(board, highlightSquare);
        
        // Create a board with empty squares as spaces.
        std::array<std::array<std::string, 8>, 8> char_board;
        for (auto &row : char_board) {
            row.fill(" ");
        }

        // Place the pieces on the board from your bitboards.
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 64; j++) {
                if (getBit(bitboards[i], j)) {
                    char_board[j / 8][j % 8] = pieceUnicode[i];
                }
            }
        }

        // Convert highlightSquare enum to int for comparison
        int highlightIndex = static_cast<int>(highlightSquare);

        // Get occupancy bitboard for highlighting
        uint64_t occupiedSquares = board.getOccupancy();

        // Print the board.
        for (int i = 7; i >= 0; i--) {
            for (int j = 0; j < 8; j++) {
                // Compute the square index.
                int square = i * 8 + j;
                bool isLightSquare = ((i + j) % 2 == 0);
                std::string bg;

                if (highlight && square == highlightIndex) {
                    bg = BG_SELECTED;  // Solid blue for selected piece
                }
                else if (highlight && getBit(movesBitboard, square)) {
                    if (getBit(occupiedSquares, square)) {
                        bg = BG_CAPTURE;  // Solid red for captures
                    }
                    else {
                        bg = isLightSquare ? BG_MOVES_LIGHT : BG_MOVES_DARK;  // Semi-transparent yellow for moves
                    }
                }
                else if (prevMove.has_value() && square == enumToInt(from)) { // Highlight the previous move
                    bg = isLightSquare ? BG_MOVES_LIGHT : BG_MOVES_DARK; 
                }
                else if (prevMove.has_value() && square == enumToInt(to)) { // Highlight the previous move
                    bg = isLightSquare ? BG_MOVES_LIGHT : BG_MOVES_DARK; 
                }
                else {
                    bg = isLightSquare ? BG_LIGHT : BG_DARK;  // Default alternating board colors
                }

                std::cout << bg << " " << char_board[i][j] << " " << RESET;
            }
            std::cout << std::endl;
        }

        std::cout << std::endl;

    }



    void printPiece(const Board &board, PieceType piece){

        std::array<uint64_t, 12> bitboards = board.getBitboards();

        int piecePos = enumToInt(piece);
        std::cout << "Printing Piece... ";
        std::cout << pieceNames[piecePos] << std::endl;

        // Create a board with empty squares as spaces.
        std::array<std::array<std::string, 8>, 8> char_board;
        for (auto &row : char_board) {
            row.fill(" ");
        }

        // Place only the specified piece into the char_board.
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 64; j++) {
                if (getBit(bitboards[i], j) && i == enumToInt(piece)) {
                    char_board[j / 8][j % 8] = pieceUnicode[i];
                }
            }
        }

        // Print the board.
        for (int i = 7; i >= 0; i--) {
            for (int j = 0; j < 8; j++) {
                // Compute the square index.
                int square = i * 8 + j;
                std::string bg;

                bool isLightSquare = ((i + j) % 2 == 0);
                bg = isLightSquare ? BG_LIGHT : BG_DARK;
                

                std::cout << bg << " " << char_board[i][j] << " " << RESET;
            }
            std::cout << std::endl;
        }
    }


    void printBitboard(uint64_t bitboard){
        // Create a board with empty squares as spaces.
        std::array<std::array<std::string, 8>, 8> char_board;
        for (auto &row : char_board) {
            row.fill(" ");
        }

        // Place only the specified piece into the char_board.
        for (int j = 0; j < 64; j++) {
            if (getBit(bitboard, j)) {
                char_board[j / 8][j % 8] = "◯";
            }
        }

        // Print the board.
        for (int i = 7; i >= 0; i--) {
            for (int j = 0; j < 8; j++) {
                // Compute the square index.
                int square = i * 8 + j;
                std::string bg;

                bool isLightSquare = ((i + j) % 2 == 0);
                bg = isLightSquare ? BG_LIGHT : BG_DARK;
                

                std::cout << bg << " " << char_board[i][j] << " " << RESET;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }



    void highlightPiece(const Board &board, PieceType piece){
        std::cout << "Highlighting Piece... ";
        std::cout << pieceNames[enumToInt(piece)] << std::endl;

        std::array<uint64_t, 12> bitboards = board.getBitboards();
        
        // Create a board with empty squares as spaces.
        std::array<std::array<std::string, 8>, 8> char_board;
        for (auto &row : char_board) {
            row.fill(" ");
        }

        // Place the pieces on the board from your bitboards.
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 64; j++) {
                if (getBit(bitboards[i], j)) {
                    char_board[j / 8][j % 8] = pieceUnicode[i];
                }
            }
        }

        uint64_t pieces = board.getAllPieces(piece);

        // Print the board.
        for (int i = 7; i >= 0; i--) {
            for (int j = 0; j < 8; j++) {
                // Compute the square index.
                int square = i * 8 + j;
                std::string bg;

                if (getBit(pieces, square)) {
                    bg = BG_SELECTED;  // Highlight selected piece
                }
                else {
                    bool isLightSquare = ((i + j) % 2 == 0);
                    bg = isLightSquare ? BG_LIGHT : BG_DARK;
                }

                std::cout << bg << " " << char_board[i][j] << " " << RESET;
            }
            std::cout << std::endl;
        }
    }


}

}