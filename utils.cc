#include "utils.h"
#include <iostream>
using namespace std;
Position::Position(int row, int col): row{row}, col{col} {}

Position::Position(const Position &p){
    row = p.row;
    col = p.col;
}

Position Position::operator=(const Position &p){
    Position newPos{p};
    row = newPos.row;
    col = newPos.col;
    return *this;
}

bool Position::operator==(const Position& p) const {
    return (row == p.row && col == p.col);
}

bool Position::operator!=(const Position& p) const {
    return (row != p.row || col != p.col);
}

Position stringToPosition (std::string s){
    int col = (int)s[0] - (int)'a';
    
    int row = (int)'8' - (int)s[1];
    Position p{row, col};

    return p;
}

Move::Move(Position start, Position end):start{start}, end{end}{}

