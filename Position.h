#ifndef POSITION_H
#define POSITION_H
#include <string>
struct Position{
    int row;
    int col;
    Position(std::string s);
    Position();
    int getRowIndex();
    int getColumnIndex();
};
#endif