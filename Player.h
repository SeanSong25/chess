#ifndef PLAYER_H
#define PLAYER_H
#include "utils.h"
#include "memory"
class ChessBoard;
class Player{
private:
    std::shared_ptr<ChessBoard> board;
    virtual struct Move decideNextMove();
public:
    bool inCheck;
    Colour colour;
    virtual void makeMove() = 0;
    virtual ~Player(){};
};

#endif