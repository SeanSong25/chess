#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "Player.h"
#include "PlayerType.h"

class HumanPlayer : public Player {
  public:
    void makeMove() override;
    PlayerType playerType() override;
};

#endif