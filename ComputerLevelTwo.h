#ifndef COMPUTERLEVELTWO_H
#define COMPUTERLEVELTWO_H
#include "ComputerPlayer.h"
#include <memory>
class ComputerLevelTwo : public ComputerPlayer{
    public:
        ComputerLevelTwo(Colour colour);
        void setBoard(std::shared_ptr<ChessBoard> board);
    private:
        Move decideNextMove() override;
};
#endif
