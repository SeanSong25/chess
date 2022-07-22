#include "Knight.h"

// constructor
Knight::Knight(std::shared_ptr<ChessBoard> board, Colour colour, Position position): 
    Piece{board, colour, position, PieceType::KNIGHT} {}

// copy constructor
Knight::Knight(Knight &k) {
    board = k.board;
    colour = k.getColour();
    position = k.getPosition();
    pieceType = k.getPieceType();
    firstMove = k.isFirstMove();
    possibleNextPos = k.getPossibleNextPos();
    possibleCaptures = k.getPossibleCaptures();
}

// update possible next positions and possible next captures for Knight
void Knight::updatePossibleNextPos() {
    // clear all previous data
    possibleNextPos.clear();
    possibleCaptures.clear();

    int row = position.row;
    int col = position.col;

    // (x + 2, y + 1)
    if (row <= 6 && col <= 5) {
        possibleNextPos.emplace_back(row + 1, col + 2);
        if (board -> getBoard()[row + 1][col + 2] 
            && board -> getBoard()[row + 1][col + 2] -> getColour() != colour) {
                possibleCaptures.emplace_back(row + 1, col + 2);
        }
    }

    // (x - 2, y + 1)
    if (row <= 6 && col >= 2) {
        possibleNextPos.emplace_back(row + 1, col - 2);
        if (board -> getBoard()[row + 1][col - 2] 
            && board -> getBoard()[row + 1][col - 2] -> getColour() != colour) {
                possibleCaptures.emplace_back(row + 1, col - 2);
        }
    }

    // (x + 2, y - 1)
    if (row >= 1 && col <= 5) {
        possibleNextPos.emplace_back(row - 1, col + 2);
        if (board -> getBoard()[row - 1][col + 2] 
            && board -> getBoard()[row - 1][col + 2] -> getColour() != colour) {
                possibleCaptures.emplace_back(row - 1, col + 2);
        }
    } 

    // (x - 2, y - 1)
    if (row >= 1 && col >= 2) {
        possibleNextPos.emplace_back(row - 1, col - 2);
        if (board -> getBoard()[row - 1][col - 2] 
            && board -> getBoard()[row - 1][col - 2] -> getColour() != colour) {
                possibleCaptures.emplace_back(row - 1, col - 2);
        }
    }  

    // (x + 1, y + 2)
    if (row <= 5 && col <= 6) {
        possibleNextPos.emplace_back(row + 2, col + 1);
        if (board -> getBoard()[row + 2][col + 1] 
            && board -> getBoard()[row + 2][col + 1] -> getColour() != colour) {
                possibleCaptures.emplace_back(row + 2, col + 1);
        }
    }

    // (x - 1, y + 2)
    if (row <= 5 && col >= 1) {
        possibleNextPos.emplace_back(row + 2, col - 1);
        if (board -> getBoard()[row + 2][col - 1] 
            && board -> getBoard()[row + 2][col - 1] -> getColour() != colour) {
                possibleCaptures.emplace_back(row + 2, col - 1);
        }
    }

    // (x + 1, y - 2)
    if (row >= 2 && col <= 6) {
        possibleNextPos.emplace_back(row - 2, col + 1);
        if (board -> getBoard()[row - 2][col + 1] 
            && board -> getBoard()[row - 2][col + 1] -> getColour() != colour) {
                possibleCaptures.emplace_back(row - 2, col + 1);
        }
    }

    // (x - 1, y - 2)
    if (row >= 2 && col >= 1) {
        possibleNextPos.emplace_back(row - 2, col - 1);
        if (board -> getBoard()[row - 2][col - 1] 
            && board -> getBoard()[row - 2][col - 1] -> getColour() != colour) {
                possibleCaptures.emplace_back(row - 2, col - 1);
        }
    }
}

Knight *Knight::clone() {
    return new Knight(*this);
}

Knight::~Knight() {}