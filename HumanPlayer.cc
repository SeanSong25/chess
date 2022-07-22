#include "HumanPlayer.h"
#include <string>
#include <sstream>
#include <iostream>
#include "ChessBoard.h"
using namespace std;

HumanPlayer::HumanPlayer(Colour colour){
    this->colour = colour;
}

bool HumanPlayer::makeMove(){
    string line;
    getline(cin, line);
    stringstream ss(line);
    int cnt = 0;
    string word;
    struct Position tempPosition{0,0};
    struct Move move{tempPosition, tempPosition};
    char pieceType;
    while(ss >> word){
        if(cnt == 1){
            tempPosition = stringToPosition(word);
            move.start = tempPosition;
        }else if (cnt == 2){
            tempPosition = stringToPosition(word);
            move.end = tempPosition;
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
PlayerType HumanPlayer::playerType() { return PlayerType::HUMAN; }
