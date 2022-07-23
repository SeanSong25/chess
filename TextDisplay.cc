#include "TextDisplay.h"

#include <assert.h>

#include "TextModifier.h"
using namespace std;
using namespace TextColour;

TextDisplay::TextDisplay() {
    // Initialize text board
    textBoard = vector<vector<char>>(8, vector<char>(8, ' '));

    // Initialize empty tiles
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if ((r + c) % 2 == 0) {
                textBoard[r][c] = ' ';
            } else {
                textBoard[r][c] = '-';
            }
        }
    }

    // // Initialize black pieces
    // textBoard[0][0] = 'r';
    // textBoard[0][1] = 'n';
    // textBoard[0][2] = 'b';
    // textBoard[0][3] = 'q';
    // textBoard[0][4] = 'k';
    // textBoard[0][5] = 'b';
    // textBoard[0][6] = 'n';
    // textBoard[0][7] = 'r';

    // for (int i = 0; i < 8; ++i) {
    //     textBoard[1][i] = 'p';
    // }

    // // Initialize white pieces
    // textBoard[7][0] = 'R';
    // textBoard[7][1] = 'N';
    // textBoard[7][2] = 'B';
    // textBoard[7][3] = 'Q';
    // textBoard[7][4] = 'K';
    // textBoard[7][5] = 'B';
    // textBoard[7][6] = 'N';
    // textBoard[7][7] = 'R';

    // for (int i = 0; i < 8; ++i) {
    //     textBoard[6][i] = 'P';
    // }
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

char PieceToChar(Piece* piece) {
    PieceType pieceType = piece->getPieceType();
    Colour colour = piece->getColour();

    if (pieceType == ROOK && colour == WHITE) return 'R';
    if (pieceType == KNIGHT && colour == WHITE) return 'N';
    if (pieceType == BISHOP && colour == WHITE) return 'B';
    if (pieceType == QUEEN && colour == WHITE) return 'Q';
    if (pieceType == KING && colour == WHITE) return 'K';
    if (pieceType == PAWN && colour == WHITE) return 'P';

    if (pieceType == ROOK && colour == BLACK) return 'r';
    if (pieceType == KNIGHT && colour == BLACK) return 'n';
    if (pieceType == BISHOP && colour == BLACK) return 'b';
    if (pieceType == QUEEN && colour == BLACK) return 'q';
    if (pieceType == KING && colour == BLACK) return 'k';
    if (pieceType == PAWN && colour == BLACK) return 'p';

    assert("invalid convertion to piece to text display, invalid piece on board. Please check your chessboard");
}

void TextDisplay::notifyTextDisplay(const vector<vector<Piece*>>& theBoard) {
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (theBoard[r][c] != nullptr) {
                textBoard[r][c] = PieceToChar(theBoard[r][c]);
            } else {
                if ((r + c) % 2 == 0) {
                    textBoard[r][c] = ' ';
                } else {
                    textBoard[r][c] = '-';
                }
            }
        }
    }
}
