#ifndef PLAYER_H
#define PLAYER_H
#include "memory"
#include "utils.h"

class ChessBoard;
class Player {
  private:
    std::shared_ptr<ChessBoard> board;
    virtual Move decideNextMove();

  public:
    Player() = default;
    virtual ~Player() = default;

    bool inCheck;
    Colour colour;
    virtual void makeMove() = 0;

    virtual PlayerType playerType() = 0;  // Return HUMAN or COMPUTER
};

#endif