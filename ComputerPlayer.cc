#include "ComputerPlayer.h"
#include "ChessBoard.h"

bool ComputerPlayer::makeMove(){
    struct Move move;
    move = decideNextMove();
    if(board.get()->checkMove(move)){
        board.get()->makeMove(move);
        return true;
    }
    return false;
}

struct Move ComputerPlayer::computeNextMove(){
    struct Position p;
    struct Move m(p,p);
    return m;
}

struct Move ComputerPlayer::decideNextMove(){
    return computeNextMove();
}

ComputerPlayer::~ComputerPlayer(){}

