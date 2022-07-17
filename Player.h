#ifndef PLAYER_H
#define PLAYER_H
#include "Colours.h"
#include "Move.h"
#include "memory"
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
};

#endif