#include "Position.h"

bool Position::operator==(const Position& p) const {
    return (row == p.row && col == p.col);
}