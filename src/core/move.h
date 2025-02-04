#include <cstdint>  // Standard integer types
#include <array>
#include <string>
#include "core/board.h"

namespace chess {

// Move class to store move information while I get things going
// TODO: Use uint16_t for move representation for better performance

// Move codes from nibble flags
enum class MoveCode : uint8_t {
    QUIET, DOUBLE_PAWN_PUSH, KING_CASTLE, QUEEN_CASTLE, CAPTURE, EN_PASSANT, KNIGHT_PROMO, BISHOP_PROMO, ROOK_PROMO, QUEEN_PROMO, KNIGHT_PROMO_CAPTURE, BISHOP_PROMO_CAPTURE, ROOK_PROMO_CAPTURE, QUEEN_PROMO_CAPTURE
};

class Move{
    public:
        Move();
        Move(Square from, Square to, uint8_t flags);

        // Getters
        Square getFrom() const; 
        Square getTo() const;
        uint8_t getFlags() const;

        bool isCapture() const; 
        bool isPromotion() const; 
        bool isEnPassant() const; 
        bool isCastle() const;

        MoveCode getMoveCode() const;

    private:
        uint16_t moveData;

};





}