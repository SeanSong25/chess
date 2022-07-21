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

Move::Move(struct Position start, struct Position end):start{start}, end{end}{}

