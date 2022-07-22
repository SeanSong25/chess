#include "Rook.h"

// constructor
Rook::Rook(std::shared_ptr<ChessBoard> board, Colour colour, Position position): 
    Piece{board, colour, position, PieceType::ROOK} {}

// copy constructor
Rook::Rook(Rook &r) {
    board = r.board;
    colour = r.getColour();
    position = r.getPosition();
    pieceType = r.getPieceType();
    firstMove = r.isFirstMove();
    possibleNextPos = r.getPossibleNextPos();
    possibleCaptures = r.getPossibleCaptures();
}

// update possible next positions and possible next captures for Queen
void Rook::updatePossibleNextPos() {
    // clear all previous data
    possibleNextPos.clear();
    possibleCaptures.clear();

    // top
    int currRow = position.row;
    int currCol = position.col;
    while(currRow >= 1) {
        possibleNextPos.emplace_back(--currRow, currCol);
        if (board -> getBoard()[currRow][currCol]) {
            if (board -> getBoard()[currRow][currCol] -> getColour() != colour) {
               possibleCaptures.emplace_back(currRow, currCol); 
            }
            break;
        }
    }

    // bottom
    currRow = position.row;
    currCol = position.col;
    while(currRow <= 6) {
        possibleNextPos.emplace_back(++currRow, currCol);
        if (board -> getBoard()[currRow][currCol]) {
            if (board -> getBoard()[currRow][currCol] -> getColour() != colour) {
               possibleCaptures.emplace_back(currRow, currCol); 
            }
            break;
        }
    }

    // left
    currRow = position.row;
    currCol = position.col;
    while(currCol >= 1) {
        possibleNextPos.emplace_back(currRow, --currCol);
        if (board -> getBoard()[currRow][currCol]) {
            if (board -> getBoard()[currRow][currCol] -> getColour() != colour) {
               possibleCaptures.emplace_back(currRow, currCol); 
            }
            break;
        }
    }

    // right
    currRow = position.row;
    currCol = position.col;
    while(currCol <= 6) {
        possibleNextPos.emplace_back(currRow, ++currCol);
        if (board -> getBoard()[currRow][currCol]) {
            if (board -> getBoard()[currRow][currCol] -> getColour() != colour) {
               possibleCaptures.emplace_back(currRow, currCol); 
            }
            break;
        }
    }
}

Rook *Rook::clone() {
    return new Rook(*this);
}

// destructor
Rook::~Rook() {}