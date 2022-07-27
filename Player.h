#ifndef PLAYER_H
#define PLAYER_H
#include "utils.h"
#include <vector>
class ChessBoard;
class Player{
public:
    Colour getColour();
    virtual bool makeMove() = 0;
    virtual PlayerType playerType() = 0; // Return HUMAN or COMPUTER
    virtual ~Player() = 0;
    void setBoard(ChessBoard* board);
protected:
    ChessBoard* board;
    Colour colour;
    
};
#endif
