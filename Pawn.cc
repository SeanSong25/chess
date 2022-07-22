#include "Pawn.h"

// constructor
Pawn::Pawn(std::shared_ptr<ChessBoard> board, Colour colour, Position position): 
    Piece{board, colour, position, PieceType::PAWN}, enPassant{false},
    enPassantPiece{nullptr}, enPassantPosition{Position{}} {}

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

// getter for enPassant
bool Pawn::isEnPassant() {
    return enPassant;
}

// setter for enPassant and enPassantPiece
void Pawn::setEnpassant(Piece *p) {
    enPassant = true;
    enPassantPiece = p;
}

// getter for enPassantPiece
Piece *Pawn::getEnPassantPiece() {
    return enPassantPiece;
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
            if (board -> getBoard()[currRow + 1][currCol + 1] && 
                board -> getBoard()[currRow + 1][currCol + 1] -> getColour() != colour) {
                    possibleCaptures.emplace_back(currRow + 1, currCol + 1);
                    possibleNextPos.emplace_back(currRow + 1, currCol + 1);
            } 
            if (board -> getBoard()[currRow + 1][currCol - 1] && 
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
            if (board -> getBoard()[currRow - 1][currCol + 1] && 
                board -> getBoard()[currRow - 1][currCol + 1] -> getColour() != colour) {
                    possibleCaptures.emplace_back(currRow - 1, currCol + 1);
                    possibleNextPos.emplace_back(currRow - 1, currCol + 1);
            } 
            if (board -> getBoard()[currRow - 1][currCol - 1] && 
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
        enPassantPosition = p;
        possibleNextPos.emplace_back(p);
    }
}

// check if opponent can en passant after this move
void Pawn::checkEnPassant(Position p) {
    if (abs(p.row - position.row) != 2) {
        return;
    }

    // find opponent pawns and supposed position of the pawn
    std::vector<Piece *> opponentPawns;
    if (colour == Colour::WHITE) {
        opponentPawns = board -> getBlackPawns();
        ++p.row;
    } else {
        opponentPawns = board -> getWhitePawns();
        --p.row;
    }

    for (auto &pawn : opponentPawns) {
        std::vector<Position> captures = pawn -> getPossibleCaptures();
        for (auto &capture: captures) {
            if (capture == p) {
                pawn -> setEnpassant(this);
                return;
            }
        }
    }
}

Pawn *Pawn::clone() {
    return new Pawn(*this);
}

void Pawn::afterMove() {
    firstMove = false;
    enPassant = false;
    enPassantPiece = nullptr;
    enPassantPosition = Position {};
}

// destructor
Pawn::~Pawn() {}