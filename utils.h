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
    Position();
    Position(int, int);
    Position(const Position & p);
    Position & operator=(const Position &p);
    bool operator==(const Position &) const;
    bool operator!=(const Position &) const;
};

struct Move{
    Move(Position start, Position end);
    Position start;
    Position end;
};
#endif