#include "utils.h"
Position::Position(std::string s){
    char c = s[0];
    col = (int)c - (int)'a';
    c = s[1];
    row = (int) c;
}

Position::Position(struct Position & p){
    this->row = p.row;
    this->col = p.col;
}

Position::Position(){
    row = -1;
    col = -1;
}

int Position::getRowIndex(){
    return 8 - row;
}

Position::Position(struct Position & p){
    this->row = p.row;
    this->col = p.col;
}

int Position::getColumnIndex(){
    return col;
}

Move::Move(){
    struct Position p;
    start = p;
    end = p;
}

Move::Move(struct Position start, struct Position end):start{start}, end{end}{}

void Move::setStart(struct Position p){
    start = p;
}

void Move::setEnd(struct Position p){
    end = p;
}

