#ifndef PIECE_H
#define PIECE_H
#include "utils.h"
#include "ChessBoard.h"
#include "utils.h"
#include "PieceType.h"
#include <memory>
#include <vector>

class Piece{
    protected: 
        std::shared_ptr<ChessBoard> board;
        Colour colour;
        Position position;
        PieceType pieceType;
        std::vector<Position> possibleNextPos;
        std::vector<Position> possibleCaptures;
        virtual void updatePossibleNextPos() = 0;
    public:
        Piece(std::shared_ptr<ChessBoard>, Colour, Position, PieceType);
        Colour getColour();
        Position getPosition();
        PieceType getPieceType();
        std::vector<Position> getPossibleNextPos();
        std::vector<Position> getPossibleCaptures();
        bool isMoveValid(Position);
        bool canBeCaptured(Position);
        virtual void move(Position);
        virtual bool isFirstMove();
        virtual ~Piece() = 0;
};

#endif