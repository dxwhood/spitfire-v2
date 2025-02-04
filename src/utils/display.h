#pragma once

#include "core/board.h"  
#include "core/movegen.h"  
#include <iostream>
#include <array>
#include <string>


namespace chess{


namespace Display{


    // Standard alternating colors.
    const std::string RESET    = "\033[0m";
    const std::string BG_LIGHT = "\033[47m";   // White background for light squares
    const std::string BG_DARK  = "\033[100m";  // Gray background for dark squares

    // Highlight colors.
    const std::string BG_MOVES = "\033[43m";  // Yellow background for possible moves
    const std::string BG_SELECTED  = "\033[48;5;111m"; // Blue background for the selected piece
    const std::string BG_CAPTURE   = "\033[48;5;167m";  // Red for capture moves

    // Highlighted colors with transparency effect.
    const std::string BG_MOVES_LIGHT   = "\033[48;5;221m";  // Light yellow 
    const std::string BG_MOVES_DARK    = "\033[48;5;178m";  // Darker yellow 

    // Helper Array for pieceType to String conversion
    constexpr std::array<const char*, 12> pieceNames = {
        "White Pawn", "White Knight", "White Bishop", "White Rook", "White Queen", "White King",
        "Black Pawn", "Black Knight", "Black Bishop", "Black Rook", "Black Queen", "Black King"
    };

    // Helper Array for pieceType to Char conversion
    constexpr std::array<const char, 12> pieceChars = {
        'P', 'N', 'B', 'R', 'Q', 'K',
        'p', 'n', 'b', 'r', 'q', 'k'
    };

    // Helper Array for pieceType to Unicode conversion
    constexpr std::array<const char*, 12> pieceUnicode = {
        "♙", "♘", "♗", "♖", "♕", "♔",  // White pieces
        "♟", "♞", "♝", "♜", "♛", "♚"   // Black pieces
    };


    void printBoard(const Board &board);  // Prints the board for debugging
    void printBoard(const Board &board, Square highlightSquare, bool highlight = true);
    void printPiece(const Board &board, PieceType piece);  // Prints a bitboard for debugging
    void highlightPiece(const Board &board, PieceType piece); // Highlights a piece type on the board
    void printBitboard(uint64_t bitboard);  // Prints a bitboard for debugging


}



}