#include "ScoreBoard.h"

#include <iostream>

#include "TextModifier.h"
using namespace std;
using namespace TextColour;

ScoreBoard::ScoreBoard() : whiteScore{0}, blackScore{0} {}

void ScoreBoard::printScore() {
    cout << Modifier(FG_MAGENTA) << "White: "
         << whiteScore << Modifier(FG_DEFAULT) << endl;
    cout << Modifier(FG_MAGENTA) << "Black: "
         << blackScore << Modifier(FG_DEFAULT) << endl;
}

void ScoreBoard::updateScore(Colour winner) {
    if (winner == BLACK) ++blackScore;
    if (winner == WHITE) ++whiteScore;
}

void ScoreBoard::updateTie() {
    blackScore += 0.5;
    whiteScore += 0.5;
}