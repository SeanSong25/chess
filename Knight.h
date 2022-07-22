#ifndef KNIGHT_H
#define KNIGHT_H
#include "Piece.h"

class Knight : public Piece {
    private:
        void updatePossibleNextPos() override;
    public:
        Knight(std::shared_ptr<ChessBoard>, Colour, Position); 
        Knight(Knight &k);
        Knight *clone() override;  
        ~Knight();
};

#endif