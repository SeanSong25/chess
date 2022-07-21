#include "utils.h"

Position::Position(std::string s){
    char c = s[0];
    col = (int)c - (int)'a';
    c = s[1];
    row = (int) c;
}

Position::Position() {
    row = -1;
    col = -1;
}

Position::Position(int row, int col): row{row}, col{col} {}

Position::Position(struct Position &p){
    row = p.row;
    col = p.col;
}

bool Position::operator==(const Position& p) const {
    return (row == p.row && col == p.col);
}

bool Position::operator!=(const Position& p) const {
    return (row != p.row || col != p.col);
}

int Position::getRowIndex(){
    return 8 - row;
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
