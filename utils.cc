#include "utils.h"

Position::Position(): row{-1}, col{-1} {}

Position::Position(int row, int col): row{row}, col{col} {}

Position::Position(const Position &p){
    row = p.row;
    col = p.col;
}

Position &Position::operator=(const Position &p){
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

Move::Move(struct Position start, struct Position end):start{start}, end{end}{}

