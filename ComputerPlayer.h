#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H
#include "Player.h"
#include "utils.h"

class ComputerPlayer : public Player {
  public:
    void makeMove() override;
    PlayerType playerType() override;
};

#endif