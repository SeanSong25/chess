#include "ChessBoard.h"

void ChessBoard::makeMove(struct Move){
}

void ChessBoard::promote(struct Move, char pieceType){
}

bool ChessBoard::checkMove(struct Move){return true;}

bool ChessBoard::checkPromotion(struct Move, char pieceType){return true;}

void ChessBoard::undo(){}

std::vector<struct Move> ChessBoard::getNextMoves(){
    std::vector<struct Move> m;
    return m;
}