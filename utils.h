#ifndef UTILS_H
#define UTILS_H
#include <string>
enum Colour{BLACK,WHITE};

enum PieceType{
    PAWN,
    KING,
    KNIGHT,
    QUEEN,
    ROOK,
    BISHOP
};

enum PlayerType{
    HUMAN,
    COMPUTER
};


struct Position{
    int row;
    int col;
    Position(std::string s);
    Position();
    int getRowIndex();
    int getColumnIndex();
};

struct Move{
    Move();
    Move(Position start, Position end);
    struct Position start;
    struct Position end;
    void setStart(struct Position p);
    void setEnd(struct Position p);
};
#endif