#ifndef BISHOP_H
#define BISHOP_H
#include "Piece.h"

class Bishop : public Piece {
    private:
        void updatePossibleNextPos() override;
    public:
        Bishop(ChessBoard*, Colour, Position);
        Bishop(Bishop &);
        Bishop *clone() override;
        ~Bishop();
};

#endif