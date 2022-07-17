#include "ComputerPlayer.h"
#include "ChessBoard.h"

void ComputerPlayer::makeMove(){
    struct Move move = decideNextMove();
    board.get()->makeMove(move);
}

ComputerPlayer::~ComputerPlayer(){}