#include "utils.h"
<<<<<<< HEAD
#include <iostream>
using namespace std;
Position::Position(int row, int col): row{row}, col{col} {}
=======

Position::Position(int row, int col) : row{row}, col{col} {}
>>>>>>> d3ca81da41c7e580c188520ced732c536d6b9d5e

Position::Position(const Position &p) {
    row = p.row;
    col = p.col;
}

<<<<<<< HEAD
Position Position::operator=(const Position &p){
=======
Position &Position::operator=(const Position &p) {
>>>>>>> d3ca81da41c7e580c188520ced732c536d6b9d5e
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

<<<<<<< HEAD
Position stringToPosition (std::string s){
    int col = (int)s[0] - (int)'a';
    
    int row = (int)'8' - (int)s[1];
    Position p{row, col};

    return p;
=======
Position stringToPosition(std::string s) {
    int col = (int)s[0] - 'a';
    int row = 8 - (s[1] - '0');
    return {row, col};
>>>>>>> d3ca81da41c7e580c188520ced732c536d6b9d5e
}

Move::Move(Position start, Position end) : start{start}, end{end} {}
