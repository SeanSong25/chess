#ifndef PIECE_H
#define PIECE_H
#include "Colours.h"
#include "ChessBoard.h"
#include "Position.h"
#include "PieceType.h"
#include <memory>
#include <vector>

class Piece{
    private: 
        std::shared_ptr<ChessBoard> board;
        Colour colour;
        Position position;
        PieceType pieceType;
        std::vector<Position> possibleNextPos;
        std::vector<Position> possibleCaptures;
        virtual std::vector<Position> getPossibleNextPos() = 0;
    public:
        Piece(std::shared_ptr<ChessBoard>, Colour, Position, PieceType);
        bool isMoveValid(Position);
        virtual void move(Position);
        virtual ~Piece() = 0;
};

#endif