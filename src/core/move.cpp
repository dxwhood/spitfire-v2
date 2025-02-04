#include "core/move.h"

namespace chess {

    Move::Move() : moveData(0) {};

    Move::Move(Square from, Square to, uint8_t flags)
    : moveData((static_cast<uint16_t>(from) & 0x3F) |       // Bits 0-5: from square
                ((static_cast<uint16_t>(to) & 0x3F) << 6) | // Bits 6-11: to square
                ((flags & 0xF) << 12)) {}                  // Bits 12-15: flags
                
        
    // Getters
    Square Move::getFrom() const { return static_cast<Square>(moveData & 0x3F); }
    Square Move::getTo() const { return static_cast<Square>((moveData >> 6) & 0x3F); }
    uint8_t Move::getFlags() const { return static_cast<uint8_t>((moveData >> 12) & 0xF); }

    bool Move::isCapture() const { return getFlags() & 0b0001'0000; } // Bit 4
    bool Move::isPromotion() const { return getFlags() & 0b1000; }    // Bit 3
    bool Move::isEnPassant() const { return getFlags() == 5; }        // Flag 5 = En passant
    bool Move::isCastle() const { return getFlags() == 2 || getFlags() == 3; }
    
    MoveCode Move::getMoveCode() const { return static_cast<MoveCode>(getFlags()); }



}