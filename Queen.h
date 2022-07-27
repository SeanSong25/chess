#ifndef QUEEN_H
#define QUEEN_H
#include "Piece.h"

class Queen : public Piece {
    private:
        void updatePossibleNextPos() override;
    public:
        Queen(ChessBoard*, Colour, Position);
        Queen(Queen &);
        Queen *clone() override;
        ~Queen();
};

#endif
