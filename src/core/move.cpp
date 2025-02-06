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

    bool Move::isQuiet() const { return getFlags() == 0; }            // Flag 0 = Quiet move
    bool Move::isCapture() const { return getFlags() & 0b0100; } 
    bool Move::isPromotion() const { return getFlags() & 0b1000; }    // 
    bool Move::isEnPassant() const { return getFlags() == 5; }        // Flag 5 = En passant
    bool Move::isCastle() const { return getFlags() == 2 || getFlags() == 3; }
    
    MoveCode Move::getMoveCode() const { return static_cast<MoveCode>(getFlags()); }

    std::string Move::toUCIString() const {
        MoveCode code = getMoveCode();
        std::string move;
        move += static_cast<char>('a' + enumToInt(getFrom()) % 8);
        move += static_cast<char>('1' + enumToInt(getFrom()) / 8);
        move += static_cast<char>('a' + enumToInt(getTo()) % 8);
        move += static_cast<char>('1' + enumToInt(getTo()) / 8);

        if (isPromotion()) {
            switch (code) {
                case MoveCode::KNIGHT_PROMO: move += 'n'; break;
                case MoveCode::BISHOP_PROMO: move += 'b'; break;
                case MoveCode::ROOK_PROMO: move += 'r'; break;
                case MoveCode::QUEEN_PROMO: move += 'q'; break;
                default: break;
            }
        }

        return move;
    }

    std::ostream& operator<<(std::ostream& os, const Move& move){
        std::string st = move.toUCIString();
        st += " ";
        st += MOVE_CODE_STRINGS[enumToInt(move.getMoveCode())];
        os << st;
        return os;
    }

    bool operator==(const Move& lhs, const Move& rhs){
        return lhs.moveData == rhs.moveData;
    }

}