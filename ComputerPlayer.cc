#include "ComputerPlayer.h"
#include "ChessBoard.h"

bool ComputerPlayer::makeMove(){
    
    Move move = decideNextMove();
    if(board.get()->checkMove(move)){
        board.get()->makeMove(move);
        return true;
    }
    return true;
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
