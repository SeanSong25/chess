#include "Move.h"

Move::Move(){
    struct Position p;
    start = p;
    end = p;
}

Move::Move(struct Position start, struct Position end):start{start}, end{end}{}

void Move::setStart(struct Position p){
    start = p;
}

void Move::setEnd(struct Position p){
    end = p;
}

