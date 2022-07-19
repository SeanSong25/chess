#include "TextDisplay.h"

#include "TextModifier.h"
using namespace std;
using namespace TextColour;

TextDisplay::TextDisplay() {
    // Initialize text board
    textBoard = vector<vector<char>>(8, vector<char>(8, ' '));

    // Initialize empty tiles
    for (int r = 2; r < 6; ++r) {
        for (int c = 0; c < 8; ++c) {
            if ((r + c) % 2 == 0) {
                textBoard[r][c] = ' ';
            } else {
                textBoard[r][c] = '-';
            }
        }
    }

    // Initialize black pieces
    textBoard[0][0] = 'r';
    textBoard[0][1] = 'n';
    textBoard[0][2] = 'b';
    textBoard[0][3] = 'q';
    textBoard[0][4] = 'k';
    textBoard[0][5] = 'b';
    textBoard[0][6] = 'n';
    textBoard[0][7] = 'r';

    for (int i = 0; i < 8; ++i) {
        textBoard[1][i] = 'p';
    }

    // Initialize white pieces
    textBoard[7][0] = 'R';
    textBoard[7][1] = 'N';
    textBoard[7][2] = 'B';
    textBoard[7][3] = 'Q';
    textBoard[7][4] = 'K';
    textBoard[7][5] = 'B';
    textBoard[7][6] = 'N';
    textBoard[7][7] = 'R';

    for (int i = 0; i < 8; ++i) {
        textBoard[6][i] = 'P';
    }
}

ostream& operator<<(ostream& out, const TextDisplay& td) {
    out << Modifier(FG_WHITE) << "------------" << Modifier(FG_DEFAULT) << endl;

    for (int r = 0; r < 8; ++r) {
        out << 8 - r << ' ';
        for (int c = 0; c < 8; ++c) {
            if (islower(td.textBoard[r][c])) {
                out << Modifier(FG_BLACK) << td.textBoard[r][c]
                    << Modifier(FG_DEFAULT);
            } else {
                out << Modifier(FG_WHITE) << td.textBoard[r][c]
                    << Modifier(FG_DEFAULT);
            }
        }
        out << endl;
    }

    out << endl;
    out << "  abcdefgh" << endl;
    out << Modifier(FG_WHITE) << "------------" << Modifier(FG_DEFAULT);
    return out;
}
