#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H
#include "Player.h"
class ComputerPlayer: public Player{
    public:
        void makeMove() override;
        virtual ~ComputerPlayer();
    private:
        struct Move decideNextMove() override;
        virtual struct Move computeNextMove();
};

#endif