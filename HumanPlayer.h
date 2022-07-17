#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "Player.h"
#include <iostream>
class HumanPlayer : Player{
    public:
        void makeMove() override;
        HumanPlayer(Colour colour);
        ~HumanPlayer();
    private:
        struct Move decideNextMove() override;
        void resign();
    
};

#endif