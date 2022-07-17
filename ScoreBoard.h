#ifndef SCORE_BOARD_H
#define SCORE_BOARD_H
#include "Colours.h"

class ScoreBoard {
    float whiteScore;
    float blackScore;

  public:
    ScoreBoard();
    ~ScoreBoard() = default;
    void printScore();
    void updateScore(Colour winner);
};

#endif