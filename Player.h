#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include <vector>

#include "utils.h"
class ChessBoard;
class Player {
  public:
    Colour getColour();
    virtual bool makeMove() = 0;
    void setBoard(std::shared_ptr<ChessBoard> board);
    virtual PlayerType playerType() = 0;  // Return HUMAN or COMPUTER
    virtual ~Player() = default;
    void setBoard(std::shared_ptr<ChessBoard> board);
protected:
    std::shared_ptr<ChessBoard> board;
    Colour colour;
    
};
#endif