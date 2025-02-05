#pragma once

#include <cstdint>  // Standard integer types
#include <array>
#include <string>
#include "core/definitions.h"

namespace chess {

// Move class to store move information while I get things going
// TODO: Use uint16_t for move representation for better performance

class Move{
    public:
        Move();
        Move(Square from, Square to, uint8_t flags);

        // Getters
        Square getFrom() const; 
        Square getTo() const;
        uint8_t getFlags() const;

        bool isQuiet() const;
        bool isCapture() const; 
        bool isPromotion() const; 
        bool isEnPassant() const; 
        bool isCastle() const;

        MoveCode getMoveCode() const;

        std::string toUCIString() const;

        friend std::ostream& operator<<(std::ostream& os, const Move& move);
    
    private:
        uint16_t moveData;

};





}