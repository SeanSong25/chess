#include "ComputerPlayer.h"
#include "ChessBoard.h"

bool ComputerPlayer::makeMove(){
    struct Move move = decideNextMove();
    if(board.get()->checkMove(move)){
        board.get()->makeMove(move);
        return true;
    }
    return false;
}

ComputerPlayer::~ComputerPlayer(){}