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
    struct Move m;
    return m;
}

bool HumanPlayer::makeMove(){
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
        if(board.get()->checkMove(move)){
            board.get()->makeMove(move);
            return true;
        }else{
            return false;
        }
    }else{
        if(board.get()->checkPromotion(move, pieceType)){
            board.get()->promote(move, pieceType);
            return true;
        }else{
            return false;
        }
    }
}

HumanPlayer::~HumanPlayer(){}