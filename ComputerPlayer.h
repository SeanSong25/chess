#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H
#include "Player.h"
class ComputerPlayer: public Player{
    public:
        bool makeMove() override;
        virtual ~ComputerPlayer();
    private:
        virtual struct Move computeNextMove();
        struct Move decideNextMove() override;
    protected:
        std::shared_ptr<ChessBoard> board;
};

#endif