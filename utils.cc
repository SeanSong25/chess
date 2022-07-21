#include "utils.h"

Position::Position(int row, int col): row{row}, col{col} {}

bool Position::operator==(const Position& p) const {
    return (row == p.row && col == p.col);
}

bool Position::operator!=(const Position& p) const {
    return (row != p.row || col != p.col);
}