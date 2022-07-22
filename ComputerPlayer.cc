#include "ComputerPlayer.h"
#include "ChessBoard.h"

bool ComputerPlayer::makeMove(){
    Move move = decideNextMove();
    if(move.start.row == -1 && move.start.col == -1){return false;} 
    //if the start index is -1, it means there is no valid moves, return valse
    board.get()->makeMove(move);
    //successfully found a valid move, return true;
    return true;
}


ComputerPlayer::~ComputerPlayer(){}
PlayerType ComputerPlayer::playerType() { return PlayerType::COMPUTER; }
