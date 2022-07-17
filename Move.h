#ifndef MOVE_H
#define MOVE_H
#include "Position.h"
struct Move{
    Move(Position start, Position end);
    struct Position start;
    struct Position end;
    void setStart(struct Position p);
    void setEnd(struct Position p);
};
#endif