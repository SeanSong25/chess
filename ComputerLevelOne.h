#ifndef COMPUTERLEVELONE_H
#define COMPUTERLEVELONE_H
#include "ComputerPlayer.h"
#include <memory>
class ComputerLevelOne : public ComputerPlayer{
    public:
        ComputerLevelOne(Colour colour);
        void setBoard(ChessBoard* board);
    private:
        struct Move computeNextMove() override;
};
#endif
