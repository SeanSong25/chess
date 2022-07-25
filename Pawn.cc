#include "Pawn.h"

// constructor
Pawn::Pawn(ChessBoard* board, Colour colour, Position position): 
    Piece{board, colour, position, PieceType::PAWN} {}

// copy constructor
Pawn::Pawn(Pawn & p) {
    board = p.board;
    colour = p.getColour();
    position = p.getPosition();
    pieceType = p.getPieceType();
    firstMove = p.isFirstMove();
    possibleNextPos = p.getPossibleNextPos();
    possibleCaptures = p.getPossibleCaptures();
    enPassant = p.isEnPassant();
    enPassantPiece = p.getEnPassantPiece();
}

// update possible next positions and possible next captures for Queen
void Pawn::updatePossibleNextPos() {
    // clear all previous data
    possibleNextPos.clear();
    possibleCaptures.clear();

    // basic: one square forward
    int currRow = position.row;
    int currCol = position.col;


    if (colour == Colour::BLACK) {
        if (currRow <= 6) {
            if (!board -> getBoard()[currRow + 1][currCol]) {
                possibleNextPos.emplace_back(currRow + 1, currCol);
            }
            if (firstMove && currRow <= 5 && !board -> getBoard()[currRow + 1][currCol] &&
                !board -> getBoard()[currRow + 2][currCol]) {
                possibleNextPos.emplace_back(currRow + 2, currCol);
            }
            // check diagonally for captures
            if (currCol < 7 && board -> getBoard()[currRow + 1][currCol + 1] && 
                board -> getBoard()[currRow + 1][currCol + 1] -> getColour() != colour) {
                    possibleCaptures.emplace_back(currRow + 1, currCol + 1);
                    possibleNextPos.emplace_back(currRow + 1, currCol + 1);
                    
            } 
            if (currCol > 0 && board -> getBoard()[currRow + 1][currCol - 1] && 
                board -> getBoard()[currRow + 1][currCol - 1] -> getColour() != colour) {
                    possibleCaptures.emplace_back(currRow + 1, currCol - 1);
                    possibleNextPos.emplace_back(currRow + 1, currCol - 1);
            } 
        }
    } else {
        if (currRow >= 1) {
            if (!board -> getBoard()[currRow - 1][currCol]) {
                possibleNextPos.emplace_back(currRow - 1, currCol);
            }
            if (firstMove && currRow >= 2 && !board -> getBoard()[currRow - 1][currCol] &&
                !board -> getBoard()[currRow - 2][currCol]) {
                possibleNextPos.emplace_back(currRow - 2, currCol);
            }  
            // check for captures
            if (currCol < 7 && board -> getBoard()[currRow - 1][currCol + 1] && 
                board -> getBoard()[currRow - 1][currCol + 1] -> getColour() != colour) {
                    possibleCaptures.emplace_back(currRow - 1, currCol + 1);
                    possibleNextPos.emplace_back(currRow - 1, currCol + 1);
            } 
            if (currCol > 0 && board -> getBoard()[currRow - 1][currCol - 1] && 
                board -> getBoard()[currRow - 1][currCol - 1] -> getColour() != colour) {
                    possibleCaptures.emplace_back(currRow - 1, currCol - 1);
                    possibleNextPos.emplace_back(currRow - 1, currCol - 1);
            } 
        }
    }


    // en passant
    // can capture pawn
    if (enPassant) {
        Position p = enPassantPiece -> getPosition();
        possibleCaptures.emplace_back(p);
        if (enPassantPiece -> getColour() == Colour::BLACK) {
            --p.row;  
        } else {
            ++p.row;
        }
        possibleNextPos.emplace_back(p);
    }
}

// check if opponent can en passant after this move
void Pawn::checkEnPassant(Position p) {

    if (abs(p.row - position.row) != 2) {
        return;
    }

    Position newPos = p;

    // find opponent pawns and supposed position of the pawn
    std::vector<Piece *> opponentPawns;
    if (colour == Colour::WHITE) {
        opponentPawns = board -> getBlackPawns();
        ++newPos.row;
    } else {
        opponentPawns = board -> getWhitePawns();
        --newPos.row;
    }

    // check if it could have been captured by another pawn
    Position captureOne;
    Position captureTwo;
    for (auto &pawn : opponentPawns) {
        if (colour == Colour::WHITE) {
            captureOne.row = pawn -> getPosition().row + 1;
            captureOne.col = pawn -> getPosition().col + 1;
            captureTwo.row = pawn -> getPosition().row + 1;
            captureTwo.row = pawn -> getPosition().col - 1;
        } else {
            captureOne.row = pawn -> getPosition().row - 1;
            captureOne.col = pawn -> getPosition().col + 1;
            captureTwo.row = pawn -> getPosition().row - 1;
            captureTwo.row = pawn -> getPosition().col - 1;
        }
        if (captureOne.row >= 0 && captureOne.col >= 0 && captureOne == newPos) {
            pawn -> setEnPassant(true, this, captureOne);
        } else if (captureTwo.row >= 0 && captureTwo.col >= 0 && captureTwo == newPos) {
            pawn -> setEnPassant(true, this, captureTwo);
        }
    }
}

Pawn *Pawn::clone() {
    return new Pawn(*this);
}

// destructor
Pawn::~Pawn() {}