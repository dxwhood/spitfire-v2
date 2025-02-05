#pragma once

#include <cstdint>  // Standard integer types
#include <array>
#include <string>
#include <iostream>
#include <optional>
#include <stack>
#include "definitions.h"
#include "move.h"

namespace chess {

class Board {
public:
    Board();  // Constructor
    void clearBoard();  // Clears the board

    void setPieces(uint64_t bitboard, PieceType piece); // Sets a piece type on the board based on a bitboard
    void clearPieceType(uint64_t bitboard, PieceType piece); // Clears a piece type on the board based on a bitboard
    void setDebugPosition();  // Sets the mid game position for debugging
   
    // Game related functions
    void setDefaultPosition();  // Sets the default starting position
    void setPiece(PieceType piece, Square square);  // Sets a piece on the board
    void movePiece(Square from, Square to);  // Moves a piece on the board
    void clearPiece(Square square);  // Clears a piece on the board

    Color getPieceColor(Square square) const;  // Returns the color of a piece on a square
    std::optional<PieceType> getPieceType(Square square) const;  // Returns the piece type on a square

    uint64_t getAllPieces(PieceType piece) const;  // Returns the bitboard for a piece type
    uint64_t getOccupancy() const;
    uint64_t getOccupancy(Color color) const;
    uint64_t getEmpty() const;
    uint64_t getWhiteOccupancy() const;
    uint64_t getBlackOccupancy() const;

    // Getters
    std::array<uint64_t, 12> getBitboards() const;
    Square getEnPassantSquare() const;


    // Making and unmaking moves
    void makeMove(Move move);
    void unmakeMove(Move move);
    

private:
    std::array<uint64_t, 12> bitboards;  // Bitboard for each piece type
    bool isWhiteTurn; // Is it white's turn?
    std::array<bool, 4> castlingRights;  // Castling rights for both players (KQkq)
    Square enPassantSquare;  // En passant square
    uint8_t halfmoveClock;  // Halfmove clock
    std::stack<MoveState> moveHistory;
};



}  // namespace chess
