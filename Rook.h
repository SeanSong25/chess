#ifndef ROOK_H
#define ROOK_H
#include "Piece.h"

class Rook : public Piece {
    private:
        bool isFirstMove;
    public:
        bool isFirstMove() override;
};

#endif