#include "ComputerLevelOne.h"
#include "ChessBoard.h"
using namespace std;
ComputerLevelOne::ComputerLevelOne(Colour col){
    colour = col;
}

void ComputerLevelOne::setBoard(shared_ptr<ChessBoard> board){
    this->board = board;
}

struct Move ComputerLevelOne::computeNextMove(){
    vector<struct Move> nextMoves;
    nextMoves = board.get()->getNextMoves();
    
    int moveIndex = 0;
    struct Move decisionMove;
    if(nextMoves.size() == 1){
        decisionMove = nextMoves[0];
        board.get()->commitMove(decisionMove);
    }
    else{
        moveIndex = rand()%nextMoves.size();
        decisionMove = nextMoves[moveIndex];
        board.get()->makeMove(decisionMove);
        
    }
}