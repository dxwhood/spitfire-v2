#include "board.h"
#include "utils/display.h"



using namespace chess;


Board::Board() {
    for (int i = 0; i < 12; i++) {
        bitboards[i] = 0;
    }
    for (int i = 0; i < 64; i++) {
        squares[i] = std::nullopt;
    }

    for (int i = 0; i < 4; i++) {
        castlingRights[i] = false;
    }
    enPassantSquare = Square::A1;
    halfmoveClock = 0;
    isWhiteTurn = true;
}

void Board::clearBoard() {
    for (int i = 0; i < 12; i++) {
        bitboards[i] = 0;
    }
    for (int i = 0; i < 64; i++) {
        squares[i] = std::nullopt;
    }
    // clear the repition table unordered map
    repetitionTable.clear();
}

void Board::setPieces(uint64_t bitboard, PieceType piece){
    bitboards[enumToInt(piece)] = bitboard;
}

void Board::clearPieceType(uint64_t bitboard, PieceType piece){
    bitboards[enumToInt(piece)] &= ~bitboard;
    for(int i=0; i<64; i++){
        if(getPieceType(static_cast<Square>(i)) == piece){
            squares[i] = std::nullopt;
        }
    }
}

void Board::setDefaultPosition(){
    clearBoard();
    for(int i=0; i<12; i++){
        bitboards[i] = STARTING_POSITIONS[i];
    }
    for (int i = 0; i < 4; i++) {
        castlingRights[i] = true;
    }
    enPassantSquare = Square::A1;
    halfmoveClock = 0;
    isWhiteTurn = true;

    // Set the mailbox
    for (int i = 0; i < 64; i++) {
        squares[i] = std::nullopt;
        for(int j=0; j<12; j++){
            if(getBit(bitboards[j], i)){
                squares[i] = static_cast<PieceType>(j);
            }
        }
    }
}

// Had o3-mini-high make this to save time. Seems to work fine for now but will need testing/rewriting.
void Board::fenToBoard(std::string fen) {
    // Clear current board state.
    clearBoard();

    // Use an istringstream to split the FEN string into its components.
    std::istringstream fenStream(fen);
    std::string boardPart, activeColor, castling, enPassant;
    int halfmove, fullmove;
    fenStream >> boardPart >> activeColor >> castling >> enPassant >> halfmove >> fullmove;

    // Process the board layout.
    // The board layout consists of 8 rank strings separated by '/'
    std::istringstream boardStream(boardPart);
    std::string rankStr;
    // FEN describes ranks from 8 down to 1.
    for (int rank = 8; rank >= 1; --rank) {
        if (!std::getline(boardStream, rankStr, '/')) {
            std::cerr << "Invalid FEN: not enough ranks." << std::endl;
            return;
        }
        int file = 0;
        for (char ch : rankStr) {
            if (std::isdigit(ch)) {
                // Empty squares; advance file index by the digit value.
                file += ch - '0';
            } else {
                // Map the FEN piece character to the corresponding PieceType.
                PieceType piece;
                switch(ch) {
                    case 'P': piece = PieceType::WHITE_PAWN; break;
                    case 'N': piece = PieceType::WHITE_KNIGHT; break;
                    case 'B': piece = PieceType::WHITE_BISHOP; break;
                    case 'R': piece = PieceType::WHITE_ROOK; break;
                    case 'Q': piece = PieceType::WHITE_QUEEN; break;
                    case 'K': piece = PieceType::WHITE_KING; break;
                    case 'p': piece = PieceType::BLACK_PAWN; break;
                    case 'n': piece = PieceType::BLACK_KNIGHT; break;
                    case 'b': piece = PieceType::BLACK_BISHOP; break;
                    case 'r': piece = PieceType::BLACK_ROOK; break;
                    case 'q': piece = PieceType::BLACK_QUEEN; break;
                    case 'k': piece = PieceType::BLACK_KING; break;
                    default:
                        std::cerr << "Invalid piece character in FEN: " << ch << std::endl;
                        continue;
                }
                // Calculate the square index.
                // Our Square enum maps A1 to index 0 up to H8 = 63.
                // Given rank (8 to 1) and file (0 to 7), the index is:
                // (rank - 1) * 8 + file.
                Square sq = static_cast<Square>((rank - 1) * 8 + file);
                setPiece(piece, sq);
                ++file;
            }
        }
    }

    // Set the active color.
    isWhiteTurn = (activeColor == "w");

    // Process castling rights.
    // Order: white kingside, white queenside, black kingside, black queenside.
    castlingRights = {false, false, false, false};
    if (castling != "-") {
        for (char c : castling) {
            switch(c) {
                case 'K': castlingRights[0] = true; break;
                case 'Q': castlingRights[1] = true; break;
                case 'k': castlingRights[2] = true; break;
                case 'q': castlingRights[3] = true; break;
                default: break;
            }
        }
    }

    // Process en passant square.
    if (enPassant == "-" || enPassant.size() < 2) {
        // Use a sentinel value (here -1 cast to Square) to denote no en passant square.
        enPassantSquare = static_cast<Square>(-1);
    } else {
        // Convert the file (a-h) and rank (1-8) from algebraic notation.
        int file = enPassant[0] - 'a';
        int rankDigit = enPassant[1] - '0'; // converts char digit to int
        enPassantSquare = static_cast<Square>((rankDigit - 1) * 8 + file);
    }

    // Set the halfmove clock.
    halfmoveClock = static_cast<uint8_t>(halfmove);

    // Set the mailbox
    for (int i = 0; i < 64; i++) {
        squares[i] = std::nullopt;
        for(int j=0; j<12; j++){
            if(getBit(bitboards[j], i)){
                squares[i] = static_cast<PieceType>(j);
            }
        }
    }
}

void Board::setPiece(PieceType piece, Square square){
    setBit(bitboards[enumToInt(piece)], enumToInt(square));
    squares[enumToInt(square)] = piece;
}

void Board::clearPiece(Square square){
    if (getPieceType(square).has_value()){
        clearBit(bitboards[enumToInt(getPieceType(square).value())], enumToInt(square));
        squares[enumToInt(square)] = std::nullopt;
    }
}

void Board::movePiece(Square from, Square to){
    std::optional<PieceType> pieceOpt = getPieceType(from);
    if (!pieceOpt.has_value()) {
        std::cout << "Error (movePiece): no piece on square " << SQUARE_STRINGS[enumToInt(from)] << std::endl;
        return;
    }
    PieceType piece = pieceOpt.value();

    // clear destination square
    clearPiece(to);
    // move piece
    setPiece(piece, to);
    // clear source square
    clearPiece(from);
}

Color Board::getPieceColor(Square square) const{
    std::optional<PieceType> pieceOpt = getPieceType(square);
    if (!pieceOpt.has_value()) {
        return Color::WHITE;
    }
    return (static_cast<int>(squares[enumToInt(square)].value()) < 6 ? Color::WHITE : Color::BLACK);
}

std::optional<PieceType> Board::getPieceType(Square square) const{
    return squares[enumToInt(square)];
}

uint64_t Board::getAllPieces(PieceType piece) const{
    return bitboards[enumToInt(piece)];
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

uint64_t Board::getOccupancy() const{
    uint64_t board = 0;
    for(int i=0; i<12; i++){
        board |= bitboards[i];
    }
    return board;
}

uint64_t Board::getOccupancy(Color color) const{
    if (color == Color::WHITE) {
        return getWhiteOccupancy();
    } else {
        return getBlackOccupancy();
    }
}

uint64_t Board::getEmpty() const{
    return ~getOccupancy();
}

std::array<uint64_t, 12> Board::getBitboards() const{
    return bitboards;
}

uint64_t Board::getBitboard(PieceType piece) const{
    return bitboards[enumToInt(piece)];
}

Square Board::getEnPassantSquare() const{
    return enPassantSquare;
}

int Board::getPhase() const{
    int phase = 0;
    uint64_t occupancy = getOccupancy();
    Square square;
    while(occupancy) {
        square = static_cast<Square>(popLSB(occupancy));
        std::optional<PieceType> pieceOpt = getPieceType(square);
        if (!pieceOpt.has_value())
            continue;
        PieceType piece = pieceOpt.value();
        int pieceIndex = enumToInt(piece);
        phase += PHASE_VALUES[pieceIndex];
    }

    if (phase > TOTAL_PHASE) {
        phase = TOTAL_PHASE;
    }

    return phase;
}

std::array<bool, 4> Board::getCastlingRights() const{
    return castlingRights;
}

bool Board::getIsWhiteTurn() const{
    return isWhiteTurn;
}

uint8_t Board::getHalfmoveClock() const{
    return halfmoveClock;
}

void Board::makeMove(Move move){
    std::optional<PieceType> pieceOpt = getPieceType(move.getFrom());
    if (!pieceOpt.has_value()) {
        std::cout << "Error (makeMove): no piece on square " << SQUARE_STRINGS[enumToInt(move.getFrom())] << std::endl;
        return;
    }
    PieceType piece = pieceOpt.value();

    // Save the current state
    MoveState state;
    std::optional<PieceType> captured = getPieceType(move.getTo());
    state.prevEnPassant = enPassantSquare;
    state.prevCastleRights = castlingRights;
    state.prevHalfmoveClock = halfmoveClock;
    state.capturedPiece = captured; 
    moveHistory.push(state);

    // Move the piece
    MoveCode code = move.getMoveCode();
    Square from = move.getFrom();
    Square to = move.getTo();
    Color color = getPieceColor(from);

    // handle captures
    if (move.isCapture()) {
        clearPiece(to);
        halfmoveClock = 0;
    }

    // handle promotions
    if (move.isPromotion()) {
        clearPiece(from);
        switch (code) {
            case MoveCode::KNIGHT_PROMO:
            case MoveCode::KNIGHT_PROMO_CAPTURE:
                setPiece((color == Color::WHITE)? PieceType::WHITE_KNIGHT : PieceType::BLACK_KNIGHT, to); 
                break;
            case MoveCode::BISHOP_PROMO: 
            case MoveCode::BISHOP_PROMO_CAPTURE:
                setPiece((color == Color::WHITE)? PieceType::WHITE_BISHOP : PieceType::BLACK_BISHOP, to); 
                break;
            case MoveCode::ROOK_PROMO:
            case MoveCode::ROOK_PROMO_CAPTURE: 
                setPiece((color == Color::WHITE)? PieceType::WHITE_ROOK : PieceType::BLACK_ROOK, to); 
                break;
            case MoveCode::QUEEN_PROMO: 
            case MoveCode::QUEEN_PROMO_CAPTURE:
                setPiece((color == Color::WHITE)? PieceType::WHITE_QUEEN : PieceType::BLACK_QUEEN, to); 
                break;
            default: break;
        }
    }

    // handle other moves
    switch (code) {
        case MoveCode::QUIET:
        case MoveCode::CAPTURE:
        case MoveCode::DOUBLE_PAWN_PUSH:
            movePiece(from, to);
            break;
        
        case MoveCode::KING_CASTLE:
            if (color == Color::WHITE) {
                clearPiece(Square::E1);
                setPiece(PieceType::WHITE_KING, Square::G1);
                clearPiece(Square::H1);
                setPiece(PieceType::WHITE_ROOK, Square::F1);
                castlingRights[0] = false;
                castlingRights[1] = false;
            } else {
                clearPiece(Square::E8);
                setPiece(PieceType::BLACK_KING, Square::G8);
                clearPiece(Square::H8);
                setPiece(PieceType::BLACK_ROOK, Square::F8);
                castlingRights[2] = false;
                castlingRights[3] = false;
            }
            break;

        case MoveCode::QUEEN_CASTLE:
            if (color == Color::WHITE) {
                clearPiece(Square::E1);
                setPiece(PieceType::WHITE_KING, Square::C1);
                clearPiece(Square::A1);
                setPiece(PieceType::WHITE_ROOK, Square::D1);
                castlingRights[0] = false;
                castlingRights[1] = false;
            } else {
                clearPiece(Square::E8);
                setPiece(PieceType::BLACK_KING, Square::C8);
                clearPiece(Square::A8);
                setPiece(PieceType::BLACK_ROOK, Square::D8);
                castlingRights[2] = false;
                castlingRights[3] = false;
            }
            break;

        case MoveCode::EN_PASSANT:
            clearPiece((color == Color::WHITE) ? static_cast<Square>(enumToInt(to) - 8) : static_cast<Square>(enumToInt(to) + 8));
            movePiece(from, to);
            break;
        
        default: break;
    }

    // Update en passant square
    if (code == MoveCode::DOUBLE_PAWN_PUSH) {
        enPassantSquare = (color == Color::WHITE) ? static_cast<Square>(enumToInt(to) - 8) : static_cast<Square>(enumToInt(to) + 8);
    } else {
        enPassantSquare = Square::A1;
    }

    // Update castling rights
    if (piece == PieceType::WHITE_KING) {
        castlingRights[0] = false;
        castlingRights[1] = false;
    } else if (piece == PieceType::BLACK_KING) {
        castlingRights[2] = false;
        castlingRights[3] = false;
    } else if (piece == PieceType::WHITE_ROOK) {
        if (from == Square::A1) {
            castlingRights[1] = false;
        } else if (from == Square::H1) {
            castlingRights[0] = false;
        }
    } else if (piece == PieceType::BLACK_ROOK) {
        if (from == Square::A8) {
            castlingRights[3] = false;
        } else if (from == Square::H8) {
            castlingRights[2] = false;
        }
    }

    // Update halfmove clock (already done for captures)
    if (piece == PieceType::WHITE_PAWN || piece == PieceType::BLACK_PAWN) {
        halfmoveClock = 0;
    } else {
        halfmoveClock++;
    }

    // Switch turns
    isWhiteTurn = !isWhiteTurn;
}

void Board::unmakeMove(Move move){
    // Restore the previous state
    MoveState state = moveHistory.top();
    moveHistory.pop();

    enPassantSquare = state.prevEnPassant;
    castlingRights = state.prevCastleRights;
    halfmoveClock = state.prevHalfmoveClock;

    // Move the piece back
    movePiece(move.getTo(), move.getFrom());

    // Handle reverse promotions
    if (move.isPromotion()) {
        Color color = getPieceColor(move.getFrom());
        clearPiece(move.getFrom());
        setPiece((color == Color::WHITE)? PieceType::WHITE_PAWN : PieceType::BLACK_PAWN, move.getFrom());
    }
    
    // Restore the captured piece
    if (state.capturedPiece.has_value()) {
        setPiece(state.capturedPiece.value(), move.getTo());
    }

    // Handle castling
    MoveCode code = move.getMoveCode();
    if (code == MoveCode::KING_CASTLE) {
        if (getPieceColor(move.getFrom()) == Color::WHITE) {
            clearPiece(Square::G1);
            clearPiece(Square::F1);
            setPiece(PieceType::WHITE_KING, Square::E1);
            setPiece(PieceType::WHITE_ROOK, Square::H1);
        } else {
            clearPiece(Square::G8);
            clearPiece(Square::F8);
            setPiece(PieceType::BLACK_KING, Square::E8);
            setPiece(PieceType::BLACK_ROOK, Square::H8);
        }
    } else if (code == MoveCode::QUEEN_CASTLE) {
        if (getPieceColor(move.getFrom()) == Color::WHITE) {
            clearPiece(Square::C1);
            clearPiece(Square::D1);
            setPiece(PieceType::WHITE_KING, Square::E1);
            setPiece(PieceType::WHITE_ROOK, Square::A1);
        } else {
            clearPiece(Square::C8);
            clearPiece(Square::D8);
            setPiece(PieceType::BLACK_KING, Square::E8);
            setPiece(PieceType::BLACK_ROOK, Square::A8);
        }
    }

    // Handle en passant (add the captured pawn back)
    if (code == MoveCode::EN_PASSANT) {
        if (getPieceColor(move.getFrom()) == Color::WHITE) {
            setPiece(PieceType::BLACK_PAWN, static_cast<Square>(enumToInt(move.getTo()) - 8));
        } else {
            setPiece(PieceType::WHITE_PAWN, static_cast<Square>(enumToInt(move.getTo()) + 8));
        }
    }

    // Switch turns
    isWhiteTurn = !isWhiteTurn;
}

Square Board::getKingSquare(Color color) const{
    PieceType king = (color == Color::WHITE)? PieceType::WHITE_KING : PieceType::BLACK_KING;
    return static_cast<Square>(getLSB(bitboards[enumToInt(king)]));
}

bool Board::isOpenFile(File file) const{
    uint64_t fileMask = FILE_MASKS[enumToInt(file)];
    return (fileMask & (getBitboard(PieceType::WHITE_PAWN) | getBitboard(PieceType::BLACK_PAWN))) == 0;
}

bool Board::isSemiOpenFile(File file, Color color) const{
    uint64_t fileMask = FILE_MASKS[enumToInt(file)];
    uint64_t pawns = (color == Color::WHITE)? getBitboard(PieceType::WHITE_PAWN) : getBitboard(PieceType::BLACK_PAWN);
    return (fileMask & pawns) == 0;
}

uint64_t Board::getPawnFill(Color color, bool rear) const{
    uint64_t pawns = (color == Color::WHITE)? getBitboard(PieceType::WHITE_PAWN) : getBitboard(PieceType::BLACK_PAWN);
    if (color == Color::BLACK){
        rear = !rear;
    }
    uint64_t fill = 0ULL;
    int i;
    while (pawns){
        i = popLSB(pawns);
        fill |= ((rear)? REAR_FILL[i] : FRONT_FILL[i]);
    }
    return fill;
}

uint64_t Board::getPawnAttackFill(Color color) const{
    uint64_t pawns = (color == Color::WHITE)? getBitboard(PieceType::WHITE_PAWN) : getBitboard(PieceType::BLACK_PAWN);
    uint64_t fill = 0ULL;
    int i;
    while(pawns){
        
        fill |= (color == Color::WHITE)? FRONT_ATTACK_FILL[i] : REAR_ATTACK_FILL[i];

    }
    return fill;
}


void Board::printSquares() const{
    for (int i = 63; i >= 0; i--) {
        std::optional<PieceType> piece = squares[(i/8) * 8 + (7-i%8)];
        const char pieceStr = (piece.has_value())? pieceChars[enumToInt(piece.value())] : '.';
        std::cout << pieceStr << " ";
        if (i % 8 == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;

}