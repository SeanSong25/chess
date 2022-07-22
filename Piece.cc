#include "utils.h"
#include "Piece.h"
#include <algorithm>

// default constructor
Piece::Piece() {}

// constructor
Piece::Piece(std::shared_ptr<ChessBoard> board, Colour colour, Position position, PieceType pieceType):
    board{board}, colour{colour}, position{position}, pieceType{pieceType}, firstMove{true},
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

// getter for possible next position
std::vector<Position> Piece::getPossibleNextPos() {
    return possibleNextPos;
}

// getter for possible captures
std::vector<Position> Piece::getPossibleCaptures() {
    return possibleCaptures;
}

void Piece::setEnpassant(Piece *p) {}

// check if the move will put king in check
bool Piece::putsKingInCheck(Position p) {
    // idea: copy construct a new board, set shared_ptr board in piece
    // to the new board, and update the position
    // then call Piece::updatePossibleNextPos
    // and check if king is in check in the new board


    // // make temp board (board if the move is made)
    // std::vector<std::vector<Piece *>> newBoard;
    // for (int i = 0; i < 8; ++i) {
    //     for (int j = 0; j < 8; ++j) {
    //         // move peice to positin p
    //         // and copy the rest of the board
    //         if (i == p.row && j == p.col) {
    //             newBoard[i][j] = this -> clone();
    //             break;
    //         }
    //         if (i == position.row && j == position.col) {
    //             newBoard[i][j] = nullptr;
    //             break;
    //         }
    //         if (board -> getBoard()[i][j]) {
    //             newBoard[i][j] = board -> getBoard()[i][j] -> clone(); 
    //         } else {
    //             newBoard[i][j] = nullptr;
    //         }
    //     }
    // }

    // bool isInCheck;

    // // check if king is in check in new board
    // for (auto &i : newBoard) {
    //     for (auto &j : i) {
    //         if (j -> getPieceType() == PieceType::KING) {
    //             isInCheck = canBeCaptured(j -> getPosition());
    //         }
    //     }
    // }

    // // delete new board
    // for (int i = 0; i < 8; ++i) {
    //     for (int j = 0; j < 8; ++j) {
    //         delete newBoard[i][j];
    //     }
    //     newBoard[i].clear();
    // }
    // newBoard.clear();

    // return isInCheck;
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

// check if opponent can en passant after this move
void Piece::checkEnPassant(Position p) {}

// update piece firstMove after move
void Piece::afterMove() {
    firstMove = false;
}

// destructor
Piece::~Piece() {}