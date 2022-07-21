#include "ChessBoard.h"
using namespace std;

ChessBoard::ChessBoard() {
    // Construct 8 x 8 chessboard
    theBoard = vector<vector<Piece *>>(8, vector<Piece *>(8, nullptr));
}
ChessBoard::~ChessBoard() {
    for (int r = 0; r < theBoard.size(); ++r) {
        for (int c = 0; c < theBoard[0].size(); ++c) {
            if (theBoard[r][c]) {
                delete theBoard[r][c];
            }
        }
    }
}

void ChessBoard::defaultInit() {}

vector<vector<Piece *>> ChessBoard::getBoard() {}

vector<vector<Piece *>> getBoard() {}
vector<Piece *> getWhiteRooks() {}
vector<Piece *> getBlackRooks() {}
vector<Piece *> getWhiteKing() {}
vector<Piece *> getBlackKing() {}
vector<Piece *> getWhitePieces() {}
vector<Piece *> getBlackPieces() {}