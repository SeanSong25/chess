#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "Player.h"
#include "Piece.h"
class ChessBoard{
public:
    bool makeMove(struct Move);
    bool promote(struct Move, char pieceType);
};

#endif