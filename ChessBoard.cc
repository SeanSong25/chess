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

void ChessBoard::defaultInit() {
    // // Initialize black pawns
    // int row = 1;
    // for (int col = 0; col < 8; col++) {
    //     Position pos = {row, col};
    //     Piece::PieceColour colour = Piece::BLACK;
    //     board[row][col] = new Pawn(colour, pos);
    // }

    // // Initialize white pawns
    // row = 6;
    // for (int col = 0; col < 8; col++) {
    //     Piece::Position pos = {row, col};
    //     Piece::PieceColour colour = Piece::WHITE;
    //     board[row][col] = new Pawn(colour, pos);
    // }

    // // Initialize Rooks
    // board[0][0] = new Rook(Piece::BLACK, Piece::Position{0, 0});
    // board[7][0] = new Rook(Piece::WHITE, Piece::Position{7, 0});
    // board[0][7] = new Rook(Piece::BLACK, Piece::Position{0, 7});
    // board[7][7] = new Rook(Piece::WHITE, Piece::Position{7, 7});

    // // Initialize Knights
    // board[0][1] = new Knight(Piece::BLACK, Piece::Position{0, 1});
    // board[7][1] = new Knight(Piece::WHITE, Piece::Position{7, 1});
    // board[0][6] = new Knight(Piece::BLACK, Piece::Position{0, 6});
    // board[7][6] = new Knight(Piece::WHITE, Piece::Position{7, 6});

    // // Initialize Bishops
    // board[0][2] = new Bishop(Piece::BLACK, Piece::Position{0, 2});
    // board[7][2] = new Bishop(Piece::WHITE, Piece::Position{7, 2});
    // board[0][5] = new Bishop(Piece::BLACK, Piece::Position{0, 5});
    // board[7][5] = new Bishop(Piece::WHITE, Piece::Position{7, 5});

    // // Initialize Queens
    // board[0][3] = new Queen(Piece::BLACK, Piece::Position{0, 3});
    // board[7][3] = new Queen(Piece::WHITE, Piece::Position{7, 3});

    // // Initialize Kings
    // board[0][4] = new King(Piece::BLACK, Piece::Position{0, 4});
    // board[7][4] = new King(Piece::WHITE, Piece::Position{7, 4});
}

vector<vector<Piece *>> ChessBoard::getBoard() {
    return theBoard;
}

vector<vector<Piece *>> getBoard() {}
vector<Piece *> getWhiteRooks() {}
vector<Piece *> getBlackRooks() {}
vector<Piece *> getWhiteKing() {}
vector<Piece *> getBlackKing() {}
vector<Piece *> getWhitePieces() {}
vector<Piece *> getBlackPieces() {}