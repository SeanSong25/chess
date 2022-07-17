#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H
#include "Player.h"
class ComputerPlayer: Player{
    public:
        void makeMove() override;
        ComputerPlayer(Colour colour);
        ~ComputerPlayer();
    private:
        struct Move decideNextMove() override;
};

#endif