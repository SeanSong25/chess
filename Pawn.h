#ifndef PAWN_H
#define PAWN_H
#include "Piece.h"

class Pawn : public Piece{
    private:
        void updatePossibleNextPos() override;
    public:
        Pawn(std::shared_ptr<ChessBoard>, Colour, Position);
        Pawn(Pawn &);
        void checkEnPassant(Position) override;
        Pawn *clone() override; 
        ~Pawn();
};

#endif