#ifndef COMPUTERLEVELFIVE_H
#define COMPUTERLEVELFIVE_H
#include "ComputerPlayer.h"
#include <memory>
class ComputerLevelFive : public ComputerPlayer{
    public:
        ComputerLevelFive(Colour colour);
        void setBoard(ChessBoard* board);
    private:
        Move decideNextMove() override;
        bool canCaptureEnemyPiece(Move m);
};
#endif
