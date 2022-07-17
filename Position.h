#ifndef POSITION_H
#define POSITION_H
struct Position{
    int row;
    int col;
    bool operator==(const Position &) const;
};
#endif