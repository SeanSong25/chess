#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "Player.h"
#include "Piece.h"
class ChessBoard{
public:
    void makeMove(struct Move);
    void promote(struct Move, char pieceType);
    bool checkMove(struct Move);
    bool checkPromotion(struct Move, char pieceType);
};

#endif