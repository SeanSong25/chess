#ifndef PLAYER_H
#define PLAYER_H
#include "utils.h"
#include <memory>
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