#ifndef COMPUTERLEVELFOUR_H
#define COMPUTERLEVELFOUR_H
#include "ComputerPlayer.h"
#include <memory>
class ComputerLevelFour : public ComputerPlayer{
    public:
        ComputerLevelFour(Colour colour);
        void setBoard(ChessBoard* board);
    private:
        Move decideNextMove() override;
        bool canCaptureEnemyPiece(Move m);
};
#endif
