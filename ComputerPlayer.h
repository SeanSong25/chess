#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H
#include "Player.h"
class ComputerPlayer: public Player{
    public:
        bool makeMove() override;
        virtual ~ComputerPlayer();
    private:
        struct Move decideNextMove() override;
        virtual struct Move computeNextMove() = 0;
    protected:
        std::shared_ptr<ChessBoard> board;
};

#endif