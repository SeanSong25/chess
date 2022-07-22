#ifndef BISHOP_H
#define BISHOP_H
#include "Piece.h"

class Bishop : public Piece {
    private:
        void updatePossibleNextPos() override;
    public:
        Bishop(std::shared_ptr<ChessBoard>, Colour, Position);
        Bishop(Bishop &);
        Bishop *clone() override;
        ~Bishop();
};

#endif