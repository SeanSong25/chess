#include "Bishop.h"

// constructor
Bishop::Bishop(std::shared_ptr<ChessBoard> board, Colour colour, Position position): 
    Piece{board, colour, position, PieceType::BISHOP} {}

// update possible next positions and possible next captures for Bishop
void Bishop::updatePossibleNextPos() {
    // clear all previous data
    possibleNextPos.clear();
    possibleCaptures.clear();

    // top left
    int currRow = position.row;
    int currCol = position.col;
    while(currRow >= 1 && currCol >= 1) {
        possibleNextPos.emplace_back(--currRow, --currCol);
        if (board -> getBoard()[currRow][currCol]) {
            if (board -> getBoard()[currRow][currCol] -> getColour() != colour) {
               possibleCaptures.emplace_back(currRow, currCol); 
            }
            break;
        }
    }

    // top right
    currRow = position.row;
    currCol = position.col;
    while(currRow >= 1 && currCol <= 6) {
        possibleNextPos.emplace_back(--currRow, ++currCol);
        if (board -> getBoard()[currRow][currCol]) {
            if (board -> getBoard()[currRow][currCol] -> getColour() != colour) {
               possibleCaptures.emplace_back(currRow, currCol); 
            }
            break;
        }
    }

    // bottom left
    currRow = position.row;
    currCol = position.col;
    while(currRow <= 6 && currCol >= 1) { 
        possibleNextPos.emplace_back(++currRow, --currCol);
        if (board -> getBoard()[currRow][currCol]) {
            if (board -> getBoard()[currRow][currCol] -> getColour() != colour) {
               possibleCaptures.emplace_back(currRow, currCol); 
            }
            break;
        }
    }

    // bottom right
    currRow = position.row;
    currCol = position.col;
    while(currRow <= 6 && currCol <= 6) {
        possibleNextPos.emplace_back(++currRow, ++currCol);
        if (board -> getBoard()[currRow][currCol]) {
            if (board -> getBoard()[currRow][currCol] -> getColour() != colour) {
               possibleCaptures.emplace_back(currRow, currCol); 
            }
            break;
        }
    }
}

Bishop::~Bishop() {}