#ifndef COMPUTERLEVELTHREE_H
#define COMPUTERLEVELTHREE_H
#include "ComputerPlayer.h"
#include <memory>
class ComputerLevelThree : public ComputerPlayer{
    public:
        ComputerLevelThree(Colour colour);
        void setBoard(ChessBoard* board);
    private:
        Move decideNextMove() override;
};
#endif
