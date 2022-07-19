#include "utils.h"
#include "Piece.h"
#include <algorithm>

// constructor
Piece::Piece(std::shared_ptr<ChessBoard> board, Colour colour, Position position, PieceType pieceType):
    board{board}, colour{colour}, position{position}, pieceType{pieceType},
    possibleNextPos{std::vector<Position>()}, possibleCaptures{std::vector<Position>()} {
    // initial possible next position for the piece
    if (pieceType == PieceType::PAWN) {
        if (colour == Colour::BLACK) {
            possibleNextPos.emplace_back(position.row + 1, position.col);
        } else {
            possibleNextPos.emplace_back(position.row - 1, position.col);
        }
            
    }
}

// check if input move is valid
bool Piece::isMoveValid(Position p) {
    if (std::find(possibleNextPos.begin(), possibleNextPos.end(), p) != possibleNextPos.end()) {
        return true;
    } else {
        return false;
    }
}

// move (base class)
void Piece::move(Position p) {
    // update position
    position = p;
}

// destructor
Piece::~Piece() {}