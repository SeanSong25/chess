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
    Position(struct Position & p);
    Position();
    Position(int, int);
    int getRowIndex();
    int getColumnIndex();
    bool operator==(const Position &) const;
    bool operator!=(const Position &) const;
};

struct Move{
    Move();
    Move(struct Position start, struct Position end);
    struct Position start;
    struct Position end;
    void setStart(struct Position p);
    void setEnd(struct Position p);
};
#endif