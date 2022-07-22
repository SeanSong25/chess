#ifndef PLAYER_H
#define PLAYER_H
#include "utils.h"
#include <memory>
#include <vector>
class ChessBoard;
class Player{
public:
    Colour getColour();
    virtual bool makeMove() = 0;
    virtual PlayerType playerType() = 0; // Return HUMAN or COMPUTER
    virtual ~Player() = default;
protected:
    std::shared_ptr<ChessBoard> board;
    Colour colour;
    void setBoard(std::shared_ptr<ChessBoard> board);
};
#endif