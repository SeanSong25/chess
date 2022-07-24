#include "HumanPlayer.h"
#include <string>
#include <sstream>
#include <iostream>
#include "Knight.h"
#include "Rook.h"
#include "Pawn.h"
#include "Queen.h"
#include "King.h"
#include "Bishop.h"
#include "ChessBoard.h"
#include <algorithm>
using namespace std;

HumanPlayer::HumanPlayer(Colour colour){
    this->colour = colour;
}

bool HumanPlayer::makeMove(){
    int cnt = 0;
    string line;
    getline (cin, line);
    stringstream s{line};
    string word;
    struct Position tempPosition{0,0};
    struct Move move{tempPosition, tempPosition};
    char pieceType;
    while(s >> word){
        if(cnt == 0){
            tempPosition = stringToPosition(word);
            move.start = tempPosition;
        }else if (cnt == 1){
            tempPosition = stringToPosition(word);
            move.end = tempPosition;
        }else if(cnt == 2){
            pieceType = word[0];
        }
        cnt++;
    }

    if(cnt == 2){
        if(board->checkMove(move)){
            board->makeMove(move);
            return true;
        }else{
            return false;
        }
    }else{
        if(board->checkPromotion(move, pieceType)){
            board->promote(move, pieceType);
            return true;
        }else{
            return false;
        }
    }
}

HumanPlayer::~HumanPlayer(){}
PlayerType HumanPlayer::playerType() { return PlayerType::HUMAN; }

void placePiece(ChessBoard* board, PieceType type, Position pos, Colour col){
    if(type == KNIGHT){
        board->setPiece(new Knight(board,col,pos),pos);
    }else if(type == ROOK){
        board->setPiece(new Rook(board,col,pos),pos);
    }
    else if(type == PAWN){
        board->setPiece(new Pawn(board,col,pos),pos);
    }
    else if(type == QUEEN){
        board->setPiece(new Queen(board,col,pos),pos);
    }
    else if(type == BISHOP){
        board->setPiece(new Bishop(board,col,pos),pos);
    }
    else if(type == KING){
        board->setPiece(new King(board,col,pos),pos);
    }

}

// int main(){
//     shared_ptr<ChessBoard> board = std::make_shared<ChessBoard>();
//     HumanPlayer* hp = new HumanPlayer(WHITE);
//     Position p{0,0};
    // Knight* k = new Knight(board, WHITE, p);
    // board->setPiece(k,p);
    // hp->setBoard(board);
//     placePiece(board,PAWN,p,BLACK);
//     p = {1,1};
//     placePiece(board,PAWN,p,WHITE);
//     board->updatePiecesPossibleMoves(BLACK);
//     board->updatePiecesPossibleMoves(WHITE);
//     std::string cmd;
//     while(cin >> cmd && cmd!="quit"){
//         if(hp->makeMove()){
//             cout << "success" <<endl;
//         }
//         else{
//             cout << "failed" <<endl;
//         }
//     }
    
// }
