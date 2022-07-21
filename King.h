#ifndef KING_H
#define KING_H
#include "Piece.h"

class King : public Piece{
    private:
        bool firstMove;
        std::vector<Piece *> attackingPieces;
        void updatePossibleNextPos() override;
        bool canCastle(Piece *);
    public:
        King(std::shared_ptr<ChessBoard>, Colour, Position);
        void getAttackingPieces();
        bool isCheckMate();
        ~King();
};

#endif