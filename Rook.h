#ifndef ROOK_H
#define ROOK_H
#include "Piece.h"

class Rook : public Piece {
  private:
    void updatePossibleNextPos() override;
  public:
    Rook(ChessBoard*, Colour, Position);
    Rook(Rook &r);
    Rook *clone() override;
    ~Rook();
};

#endif
