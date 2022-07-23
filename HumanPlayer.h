#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "Player.h"
#include <iostream>
class HumanPlayer : public Player{
    public:
        bool makeMove() override;
        HumanPlayer(Colour colour);
        ~HumanPlayer();
        PlayerType playerType() override;
    private:
        bool isKingCastling(Move m);
};
#endif