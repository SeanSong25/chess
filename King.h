#ifndef KING_H
#define KING_H
#include "Piece.h"

class King : public Piece{
    private:
        std::vector<Piece *> attackingPieces;
        void updatePossibleNextPos() override;
        bool canCastle(Piece *);
    public:
        King(ChessBoard*, Colour, Position);
        King(King &k);
        std::vector<Piece *> getAttackingPieces();
        void updateAttackingPieces();
        bool isCheckMate();
        King *clone() override;
        ~King();
};

#endif