#include "HumanPlayer.h"
#include <string>
#include <sstream>
#include <iostream>
#include "Knight.h"
#include "ChessBoard.h"
#include <algorithm>
using namespace std;

HumanPlayer::HumanPlayer(Colour colour){
    this->colour = colour;
}

//check if the move entered is a king moving 2 steps
//if it is, then it is the first move of castling
bool HumanPlayer::isKingCastling(Move m){
    Position start = m.start;
    Position end = m.end;
    if(board->getBoard()[start.row][start.col]->getPieceType() != KING){
        return false;
    }
    //check if the column difference is 2
    if(abs(end.col-start.col) == 2){
        return true;
    }
    return false;
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

    if(cnt == 3){
        //check if it is castle move by checking if king has moved 2 squares
        if(isKingCastling(move)){
            //if it is a castle move, input the next move 
            string startPosition;
            string endPosition;
            cin >> word >> startPosition >> endPosition;
            tempPosition = stringToPosition(startPosition);
            //if the start position is a rook, and the end position is the position of that king 
            //is skipping over, else return falses

        }

        
        
        //check if canCastle(rook*) else 
        //if returns true, make first move, then make second move, return true
        //otherise return false
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

// int main(){
//     ChessBoard ch{};
//     shared_ptr<ChessBoard> board = make_shared<ChessBoard>(ch);
//     HumanPlayer* hp = new HumanPlayer(WHITE);
//     Position p{0,0};
//     Knight* k = new Knight(board, WHITE, p);
//     board.get()->setPiece(k,p);
//     hp->setBoard(board);
//     hp->makeMove();
// }
