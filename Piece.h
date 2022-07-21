#ifndef PIECE_H
#define PIECE_H
#include <memory>
#include <vector>
#include "ChessBoard.h"
#include "utils.h"

class ChessBoard;

class Piece{
    protected: 
        std::shared_ptr<ChessBoard> board;
        Colour colour;
        Position position;
        PieceType pieceType;
        bool firstMove;
        std::vector<Position> possibleNextPos;
        std::vector<Position> possibleCaptures;
        bool putsKingInCheck(Position);
        bool canBeCaptured(Position);
    public:
        Piece(std::shared_ptr<ChessBoard>, Colour, Position, PieceType);
        Colour getColour();
        Position getPosition();
        void setPosition(Position);
        PieceType getPieceType();
        bool isFirstMove();
        void setFirstMove(bool);
        virtual void updatePossibleNextPos() = 0;
        std::vector<Position> getPossibleNextPos();
        std::vector<Position> getPossibleCaptures();
        bool isMoveValid(Position);
        virtual ~Piece() = 0;
};

#endif