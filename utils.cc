#include "utils.h"

Position::Position(): row{-1}, col{-1} {}

Position::Position(int row, int col): row{row}, col{col} {}

Position::Position(const Position &p) {
    row = p.row;
    col = p.col;
}

Position &Position::operator=(const Position &p) {
    Position newPos{p};
    row = newPos.row;
    col = newPos.col;
    return *this;
}

bool Position::operator==(const Position &p) const {
    return (row == p.row && col == p.col);
}

bool Position::operator!=(const Position &p) const {
    return (row != p.row || col != p.col);
}

Position stringToPosition(std::string s) {
    int col = (int)s[0] - 'a';
    int row = 8 - (s[1] - '0');
    return {row, col};
}

Move::Move(Position start, Position end) : start{start}, end{end} {}
