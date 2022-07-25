#include "ComputerPlayer.h"
#include "ChessBoard.h"

bool ComputerPlayer::makeMove(){
    Move move = decideNextMove();
    if(move.start.row != -1){
        board->makeMove(move);
        return true;
    }
    return false;
}

struct Move ComputerPlayer::computeNextMove(){
    struct Position p{0,0};
    struct Move m(p,p);
    return m;
}

struct Move ComputerPlayer::decideNextMove(){
    return computeNextMove();
}

ComputerPlayer::~ComputerPlayer(){}
PlayerType ComputerPlayer::playerType() { return PlayerType::COMPUTER; }
