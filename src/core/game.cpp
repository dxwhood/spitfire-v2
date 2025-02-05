#include "game.h"

namespace chess {


Game::Game() : isWhiteTurn(true) {
    board.setDefaultPosition();
}

void Game::start(bool playerWhite) {
    Move parsedMove;
    while (true) {
        Display::printBoard(board);
        std::string move = Input::inputMove();
        while (!Input::validateInputMove(move)) {
            std::cout << "Invalid move. Please try again." << std::endl;
            move = Input::inputMove();
        }
        parsedMove = Input::parseUCIMove(board, move);

        if (isWhiteTurn && board.getPieceColor(parsedMove.getFrom()) == Color::WHITE) {
            playMove(parsedMove);
            isWhiteTurn = !isWhiteTurn;
        } else if (!isWhiteTurn && board.getPieceColor(parsedMove.getFrom()) == Color::BLACK) {
            playMove(parsedMove);
            isWhiteTurn = !isWhiteTurn;
        } else {
            std::cout << "Error: wrong color. Try again" << std::endl;
        }
    }
}


void Game::playMove(Move move) {
    MoveCode code = move.getMoveCode();
    Square from = move.getFrom();
    Square to = move.getTo();
    std::optional<PieceType> pieceOpt = board.getPieceType(from);
    if (!pieceOpt.has_value()) {
        std::cout << "Error: no piece on square" << std::endl;
        return;
    }
    PieceType piece = pieceOpt.value();

    switch (code) {
        case MoveCode::QUIET:
        case MoveCode::DOUBLE_PAWN_PUSH:
            board.setPiece(piece, to);
            board.clearPiece(from);
            break;
        case MoveCode::KING_CASTLE:
            break;
        case MoveCode::QUEEN_CASTLE:
            break;
        case MoveCode::CAPTURE:
            board.clearPiece(to);
            board.setPiece(piece, to);
            break;
        case MoveCode::EN_PASSANT:
            break;
        case MoveCode::KNIGHT_PROMO:
            break;
        case MoveCode::BISHOP_PROMO:
            break;
        case MoveCode::ROOK_PROMO:
            break;
        case MoveCode::QUEEN_PROMO:
            break;
        case MoveCode::KNIGHT_PROMO_CAPTURE:
            break;
        case MoveCode::BISHOP_PROMO_CAPTURE:
            break;
        case MoveCode::ROOK_PROMO_CAPTURE:
            break;
        case MoveCode::QUEEN_PROMO_CAPTURE:
            break;
    }
    


}






}