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
        ChessBoard* board;
        Colour colour;
        Position position;
        PieceType pieceType;
        bool firstMove;
        bool enPassant;
        Piece *enPassantPiece;
        Position enPassantPosition;
        std::vector<Position> possibleNextPos;
        std::vector<Position> possibleCaptures;
        std::vector<Position> canPhysicallyCapture;
    public:
        Piece();
        Piece(ChessBoard*, Colour, Position, PieceType);
        Colour getColour();
        Position getPosition();
        void setPosition(Position);
        PieceType getPieceType();
        bool isFirstMove();
        void setFirstMove(bool);
        bool isEnPassant();
        virtual bool isCheckMate();
        Piece *getEnPassantPiece();
        Position getEnPassantPosition();
        std::vector<Position> getPossibleNextPos();
        std::vector<Position> getPossibleCaptures();
        std::vector<Position> getPhysicallyPossibleCaptures();
        virtual void updatePossibleNextPos() = 0;
        virtual Piece *clone() = 0;
        void setEnPassant(bool, Piece *, Position);
        bool putsKingInCheck(Position);
        bool isMoveValid(Position, Colour);
        bool canBeCaptured(Position);
        virtual bool isInCheck();
        virtual void checkEnPassant(Position);
        void afterMove();
        virtual ~Piece() = 0;
        friend std::ostream &operator<<(std::ostream&, const Piece&);
};

#endif