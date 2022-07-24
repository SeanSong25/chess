#ifndef PIECE_H
#define PIECE_H
#include <memory>
#include <vector>
#include "ChessBoard.h"
#include <iostream>
#include "utils.h"

class ChessBoard;

class Piece{
    protected: 
        std::shared_ptr<ChessBoard> board;
        Colour colour;
        Position position;
        PieceType pieceType;
        bool firstMove;
        bool enPassant;
        Piece *enPassantPiece;
        Position enPassantPosition;
        std::vector<Position> possibleNextPos;
        std::vector<Position> possibleCaptures;
        bool canBeCaptured(Position);
    public:
        Piece();
        Piece(std::shared_ptr<ChessBoard>, Colour, Position, PieceType);
        Colour getColour();
        Position getPosition();
        void setPosition(Position);
        PieceType getPieceType();
        bool isFirstMove();
        void setFirstMove(bool);
        bool isEnPassant();
        Piece *getEnPassantPiece();
        Position getEnPassantPosition();
        std::vector<Position> getPossibleNextPos();
        std::vector<Position> getPossibleCaptures();
        virtual void updatePossibleNextPos() = 0;
        virtual Piece *clone() = 0;
        void setEnPassant(bool, Piece *, Position);
        bool putsKingInCheck(Position);
        bool isMoveValid(Position);
        virtual void checkEnPassant(Position);
        virtual void afterMove();
        virtual ~Piece() = 0;
};

#endif