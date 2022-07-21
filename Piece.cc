#include "utils.h"
#include "Piece.h"
#include <algorithm>

// constructor
Piece::Piece(std::shared_ptr<ChessBoard> board, Colour colour, Position position, PieceType pieceType):
    board{board}, colour{colour}, position{position}, pieceType{pieceType},
    possibleNextPos{std::vector<Position>()}, possibleCaptures{std::vector<Position>()} {
    // initial possible next position for the piece
    getPossibleNextPos();
}

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

// getter for possible next position
std::vector<Position> Piece::getPossibleNextPos() {
    return possibleNextPos;
}

// getter for possible captures
std::vector<Position> Piece::getPossibleCaptures() {
    return possibleCaptures;
}

// check if the move will put king in check
bool Piece::putsKingInCheck(Position p) {

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

// return true if king is in check
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

// destructor
Piece::~Piece() {}