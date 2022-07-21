#include "utils.h"

Position::Position(int row, int col): row{row}, col{col} {}

Position::Position(const Position &p){
    row = p.row;
    col = p.col;
}

Position &Position::operator=(const Position &p){
    Position newPos{p};
    return newPos;
}

bool Position::operator==(const Position& p) const {
    return (row == p.row && col == p.col);
}

bool Position::operator!=(const Position& p) const {
    return (row != p.row || col != p.col);
}

Position stringToPosition (std::string s){
    int col = (int)s[0] - (int)'a';
    int row = 8 - (int)s[1];
    Position p{row, col};
    return p;
}

Move::Move(struct Position start, struct Position end):start{start}, end{end}{}

