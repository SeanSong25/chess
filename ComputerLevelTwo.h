#ifndef COMPUTERLEVELTWO_H
#define COMPUTERLEVELTWO_H
#include "ComputerPlayer.h"
#include <memory>
class ComputerLevelTwo : public ComputerPlayer{
    public:
        ComputerLevelTwo(Colour colour);
        void setBoard(ChessBoard* board);
    private:
        Move decideNextMove() override;
};
#endif
