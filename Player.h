#ifndef PLAYER_H
#define PLAYER_H
#include "Colours.h"
#include <memory>
#include "Move.h"
class ChessBoard;
class Player{
private:
    virtual struct Move decideNextMove();
public:
    bool inCheck;
    Colour colour;
    virtual bool makeMove() = 0;
    virtual ~Player(){};
protected:
    std::shared_ptr<ChessBoard> board;
    void setBoard(std::shared_ptr<ChessBoard> board);
};

#endif