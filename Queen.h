#ifndef QUEEN_H
#define QUEEN_H
#include "Piece.h"

class Queen : public Piece {
    private:
        void updatePossibleNextPos() override;
    public:
        Queen(std::shared_ptr<ChessBoard>, Colour, Position);
        ~Queen();
};

#endif