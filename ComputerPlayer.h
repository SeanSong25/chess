#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H
#include "Player.h"
class ComputerPlayer: public Player{
    public:
        bool makeMove() override;
        PlayerType playerType() override;
        virtual ~ComputerPlayer() = 0;
    private:
        virtual struct Move decideNextMove() = 0;
};
#endif