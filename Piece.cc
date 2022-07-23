#include "utils.h"
#include "Piece.h"
#include <algorithm>

// default constructor
Piece::Piece() {}

// constructor
Piece::Piece(std::shared_ptr<ChessBoard> board, Colour colour, Position position, PieceType pieceType):
    board{board}, colour{colour}, position{position}, pieceType{pieceType}, firstMove{true},
    enPassant{false}, enPassantPiece{nullptr}, enPassantPosition{Position{}},
    possibleNextPos{std::vector<Position>()}, possibleCaptures{std::vector<Position>()} {}

// getter for colour
Colour Piece::getColour() {
    return colour;
}

// getter for position
Position Piece::getPosition() {
    return position;
}

// setter for position
void Piece::setPosition(Position p) {
    position = p;
}

// getter for piece type
PieceType Piece::getPieceType() {
    return pieceType;
}

// check if it is the first move (getter for firstMove)
bool Piece::isFirstMove() {
    return firstMove;
}

// setter for firstMove
void Piece::setFirstMove(bool b) {
    firstMove = b;
}

// getter for isEnPassant
bool Piece::isEnPassant() {
    return enPassant;
}

// getter for enPassantPiece
Piece *Piece::getEnPassantPiece() {
    return enPassantPiece;
}

// getter for enPassantPosition
Position Piece::getEnPassantPosition() {
    return enPassantPosition;
}

// getter for possible next position
std::vector<Position> Piece::getPossibleNextPos() {
    return possibleNextPos;
}

// getter for possible captures
std::vector<Position> Piece::getPossibleCaptures() {
    return possibleCaptures;
}

// setter for enPassant and enPassantPiece
void Piece::setEnPassant(bool b, Piece *p) {
    enPassant = b;
    enPassantPiece = p;
}

// check if the move will put king in check
bool Piece::putsKingInCheck(Position p) {
    // idea: copy construct a new board, set shared_ptr board in piece
    // to the new board, and update the position
    // then call Piece::updatePossibleNextPos
    // and check if king is in check in the new board

    std::shared_ptr<ChessBoard> newBoard = std::make_shared<ChessBoard>(*board);
    std::shared_ptr<ChessBoard> tempStoreBoard = board;
    board = newBoard;
    
    // set up the new board
    for (auto &i : board -> getBoard()) {
        for (auto &j: i) {
            j -> updatePossibleNextPos();
        }
    }

    // make move
    Move newMove{position, p};
    board -> makeMove(newMove);

    // check if king is in check in new board
    Piece *king;
    if (colour == Colour::BLACK) {
        king = board -> getBlackKing();
    } else {
        king = board -> getWhiteKing();
    }

    bool isInCheck = canBeCaptured(king -> getPosition());

    // revert fields back to original
    board = tempStoreBoard;
    for (auto &i : board -> getBoard()) {
        for (auto &j: i) {
            j -> updatePossibleNextPos();
        }
    }

    return isInCheck;
}

// check if input move is valid
bool Piece::isMoveValid(Position p) {
    // check if physcially possible
    if (std::find(possibleNextPos.begin(), possibleNextPos.end(), p) != possibleNextPos.end()) {
        // check if this move puts player's king in check
        if (putsKingInCheck(p)) {
            return false;
        }
        return true;
    } else {
        return false;
    }
}

// return true if piece can be captured by another piece
bool Piece::canBeCaptured(Position p) {
    std::vector<Piece *> opponentPieces;
    if (colour == Colour::WHITE) {
        opponentPieces = board -> getBlackPieces();
    } else {
        opponentPieces = board -> getWhitePieces();
    }

    for (auto &piece : opponentPieces) {
        std::vector<Position> captures = piece -> getPossibleCaptures();
        if (std::find(captures.begin(), captures.end(), p) != captures.end()) {
            return true;
        }
    }

    return false;
}

// check if opponent can en passant after this move
void Piece::checkEnPassant(Position p) {}

// update piece fields after move
void Piece::afterMove() {
    firstMove = false;
    enPassant = false;
    enPassantPiece = nullptr;
    enPassantPosition = Position{};
}

// destructor
Piece::~Piece() {}