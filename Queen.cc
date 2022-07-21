#include "Queen.h"

// constructor
Queen::Queen(std::shared_ptr<ChessBoard> board, Colour colour, Position position): 
    Piece{board, colour, position, PieceType::QUEEN} {}

// update possible next positions and possible next captures for Queen
void Queen::updatePossibleNextPos() {
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

    // top
    currRow = position.row;
    currCol = position.col;
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

Queen::~Queen() {}