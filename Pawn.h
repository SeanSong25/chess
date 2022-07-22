#ifndef PAWN_H
#define PAWN_H
#include "Piece.h"

class Pawn : public Piece{
    private:
        bool enPassant;
        Piece *enPassantPiece;
        Position enPassantPosition;
        void updatePossibleNextPos() override;
    public:
        Pawn(std::shared_ptr<ChessBoard>, Colour, Position);
        Pawn(Pawn &);
        bool isEnPassant();
        void setEnpassant(Piece *) override;
        Piece *getEnPassantPiece();
        void checkEnPassant(Position) override;
        Pawn *clone() override;
        void afterMove() override;
        ~Pawn();
};

#endif