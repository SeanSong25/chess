#include "HumanPlayer.h"
#include <string>
#include <sstream>
#include "ChessBoard.h"
using namespace std;

HumanPlayer::HumanPlayer(Colour colour){
    this->colour = colour;
}

void HumanPlayer::resign(){}

struct Move HumanPlayer::decideNextMove(){
    string line;
    getline(cin, line);
    stringstream ss(line);
    int cnt = 0;
    string word;
    struct Move move;
    struct Position tempPosition;
    char pieceType;
    while(ss >> word){
        if(cnt == 1){
            tempPosition = Position{word};
            move.setStart(tempPosition);
        }else if (cnt == 2){
            tempPosition = Position{word};
            move.setEnd(tempPosition);
        }else if(cnt == 3){
            pieceType = word[0];
        }
        cnt++;
    }

    if(cnt == 2){
        board.get()->makeMove(move);
    }else{
        board.get()->promote(move,pieceType);
    }
    return move;
}

void HumanPlayer::makeMove(){
    decideNextMove();
}

HumanPlayer::~HumanPlayer(){}