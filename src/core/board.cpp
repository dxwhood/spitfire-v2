#include "board.h"
#include <iostream>
#include <array>


namespace chess {


Board::Board() {
    for (int i = 0; i < 12; i++) {
        bitboards[i] = 0;
    }
}

void Board::clearBoard() {
    for (int i = 0; i < 12; i++) {
        bitboards[i] = 0;
    }
}

// Overloaded function: no highlighting; just the board.
void Board::printBoard() const {
    printBoard(Square::A1, 0ULL, false);  
}

// Overloaded function with highlighting.
// highlightSquare: Square enum value for the piece to highlight.
// movesBitboard: Bitboard of possible moves (attacks) to highlight.
// highlight: If false, ignores highlightSquare and movesBitboard (used for overload simplicity).
void Board::printBoard(Square highlightSquare, uint64_t movesBitboard, bool highlight) const {
    std::cout << "Printing Full Board..." << std::endl;
    
    // Create a board with empty squares as spaces.
    std::array<std::array<std::string, 8>, 8> board;
    for (auto &row : board) {
        row.fill(" ");
    }

    // Place the pieces on the board from your bitboards.
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 64; j++) {
            if (getBit(bitboards[i], j)) {
                board[j / 8][j % 8] = pieceUnicode[i];
            }
        }
    }

    // ANSI escape codes for background colors.
    // Standard alternating colors.
    const std::string RESET    = "\033[0m";
    const std::string BG_LIGHT = "\033[47m";   // White background for light squares
    const std::string BG_DARK  = "\033[100m";  // Gray background for dark squares
    // Highlight colors.
    const std::string BG_HIGHLIGHT = "\033[43m";  // Yellow background for possible moves
    const std::string BG_SELECTED  = "\033[44m";  // Blue background for the selected piece

    // Convert highlightSquare enum to int for comparison
    int highlightIndex = static_cast<int>(highlightSquare);

    // Print the board.
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            // Compute the square index.
            int square = i * 8 + j;
            std::string bg;

            if (highlight && square == highlightIndex) {
                bg = BG_SELECTED;  // Highlight selected piece
            }
            else if (highlight && getBit(movesBitboard, square)) {
                bg = BG_HIGHLIGHT; // Highlight possible moves
            }
            else {
                bool isLightSquare = ((i + j) % 2 == 0);
                bg = isLightSquare ? BG_LIGHT : BG_DARK;
            }

            std::cout << bg << " " << board[i][j] << " " << RESET;
        }
        std::cout << std::endl;
    }
}


void Board::printPiece(PieceType piece) const {
    int piecePos = enumToInt(piece);
    std::cout << "Printing Piece... ";
    std::cout << pieceNames[piecePos] << std::endl;

    // print board
    for(int i=8; i>0; i--){
        for (int j=8; j>0; j--){
            std::cout << getBit(bitboards[piecePos], (8*i)-j) << " ";
        }
        std::cout << std::endl;
    }

    for(int i=8; i>0; i--){
        for (int j=8; j>0; j--){
            std::cout << (8*i)-j << " ";
        }
        std::cout << std::endl;
    }
}


void Board::printBitboard(uint64_t bitboard) const{
    std::cout << "Printing Bitboard" << std::endl;
    for(int i=8; i>0; i--){
        for (int j=8; j>0; j--){
            std::cout << getBit(bitboard, (8*i)-j) << " ";
        }
        std::cout << std::endl;
    }
}


void Board::setPieceType(uint64_t bitboard, PieceType piece){
    bitboards[enumToInt(piece)] = bitboard;
}


void Board::clearPieceType(uint64_t bitboard, PieceType piece){
    bitboards[enumToInt(piece)] &= ~bitboard;
}

void Board::setDefaultPosition(){
    for(int i=0; i<12; i++){
        bitboards[i] = STARTING_POSITIONS[i];
    }
}

void Board::setDebugPosition(){
    for(int i=0; i<12; i++){
        bitboards[i] = MID_GAME_POSITIONS[i];
    }
}

void Board::setPiece(Square square, PieceType piece){
    setBit(bitboards[enumToInt(piece)], enumToInt(square));
}

void Board::clearPiece(Square square){
    // clean for loop to clear piece
    for(int i=0; i<12; i++){
        clearBit(bitboards[i], enumToInt(square));
    }
}

uint64_t Board::getPieceType(PieceType piece) const{
    return bitboards[enumToInt(piece)];
}

uint64_t Board::getOccupancy() const{
    uint64_t board = 0;
    for(int i=0; i<12; i++){
        board |= bitboards[i];
    }
    return board;
}

uint64_t Board::getWhiteOccupancy() const{
    uint64_t board = 0;
    for(int i=0; i<6; i++){
        board |= bitboards[i];
    }
    return board;
}

uint64_t Board::getBlackOccupancy() const{
    uint64_t board = 0;
    for(int i=6; i<12; i++){
        board |= bitboards[i];
    }
    return board;
}

uint64_t Board::getEmpty() const{
    return ~getOccupancy();
}





}  // namespace chess
