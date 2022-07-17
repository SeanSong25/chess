#ifndef PLAYER_H
#define PLAYER_H
#include "Colours.h"
#include "memory"
#include "Move.h"
class ChessBoard;
class Player{
protected:
    std::shared_ptr<ChessBoard> board;
    virtual struct Move decideNextMove();
public:
    bool inCheck;
    Colour colour;
    virtual void makeMove() = 0;
    virtual ~Player(){};
};

#endif