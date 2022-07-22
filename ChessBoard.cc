#include "ChessBoard.h"

#include <assert.h>

#include <algorithm>
#include <iostream>

#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"
#include "TextModifier.h"
#include "util.h"
using namespace std;

// ----------------------------------------------------------------------------
// Ctor and dtor

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

// ----------------------------------------------------------------------------
// Board setup methods

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

void ChessBoard::setupPiece() {
    using namespace TextColour;  // Included for modifying terminal text colour

    // Read in piece and position
    char p;
    string s;
    cin >> p >> s;

    Position pos = stringToPosition(s);
    int r = pos.row;
    int c = pos.col;

    // Verify the position is valid
    if (r < 0 || r > 7 || c < 0 || c > 7) {
        // cout << "Row: " << r << " Col: " << c << endl;
        cout << Modifier(FG_RED) << "Position out of range"
             << Modifier(FG_DEFAULT) << endl;
        return;
    }

    // Verity the tile is empty
    if (theBoard[r][c] != nullptr) {
        cout << Modifier(FG_RED) << "Position " << s
             << " already has a piece" << Modifier(FG_DEFAULT) << endl;
        return;
    }

    // Create piece
    switch (p) {
        // case 'r':
        // theBoard[r][c] = new Rook(shared_from_this(), BLACK, pos);
        // break;
        case 'n':
            theBoard[r][c] = new Knight(shared_from_this(), BLACK, pos);
            break;
        case 'b':
            theBoard[r][c] = new Bishop(shared_from_this(), BLACK, pos);
            break;
        case 'q':
            theBoard[r][c] = new Queen(shared_from_this(), BLACK, pos);
            break;
        case 'k':
            theBoard[r][c] = new King(shared_from_this(), BLACK, pos);
            break;
        // case 'p':
        //     theBoard[r][c] = new Pawn(shared_from_this(), BLACK, pos);
        //     break;
        // case 'R':
        // theBoard[r][c] = new Rook(shared_from_this(), WHITE, pos);
        // break;
        case 'N':
            theBoard[r][c] = new Knight(shared_from_this(), WHITE, pos);
            break;
        case 'B':
            theBoard[r][c] = new Bishop(shared_from_this(), WHITE, pos);
            break;
        case 'Q':
            theBoard[r][c] = new Queen(shared_from_this(), WHITE, pos);
            break;
        case 'K':
            theBoard[r][c] = new King(shared_from_this(), WHITE, pos);
            break;
        // case 'P':
        // theBoard[r][c] = new Pawn(shared_from_this(), WHITE, pos);
        // break;
        default:
            cout << Modifier(FG_RED) << "Invalid piece name"
                 << Modifier(FG_DEFAULT) << endl;
            return;
    }

    cout << Modifier(FG_GREEN) << "Successfully placed the piece " << p << " on the square " << s << Modifier(FG_DEFAULT) << endl;
}

void ChessBoard::removePiece() {
    using namespace TextColour;

    string p;
    cin >> p;
    Position pos = stringToPosition(p);
    int r = pos.row;
    int c = pos.col;

    // Verify the position is valid
    if (r < 0 || r > 7 || c < 0 || c > 7) {
        cout << Modifier(FG_RED) << "Position out of range"
             << Modifier(FG_DEFAULT) << endl;
        return;
    }
    // Check the square has a piece
    if (theBoard[r][c] == nullptr) {
        cout << Modifier(FG_RED) << "Square " << p << " does not have a piece" << Modifier(FG_DEFAULT) << endl;
        return;
    }
    // Delete piece
    else if (theBoard[r][c]) {
        delete theBoard[r][c];
        theBoard[r][c] = nullptr;
        cout << Modifier(FG_GREEN) << "Successfully removes piece from square " << p << Modifier(FG_DEFAULT) << endl;
    }
}
// ----------------------------------------------------------------------------
// Getters

vector<vector<Piece *>> ChessBoard::getBoard() {
    return theBoard;
}

vector<Piece *> ChessBoard::getWhiteRooks() {}
vector<Piece *> ChessBoard::getBlackRooks() {}
vector<Piece *> ChessBoard::getWhiteKing() {}
vector<Piece *> ChessBoard::getBlackKing() {}
vector<Piece *> ChessBoard::getWhitePieces() {}
vector<Piece *> ChessBoard::getBlackPieces() {}

// ----------------------------------------------------------------------------
// Game Logic

void ChessBoard::makeMove(struct Move) {
}

void ChessBoard::promote(struct Move, char pieceType) {
}

bool ChessBoard::checkMove(struct Move) { return true; }

bool ChessBoard::checkPromotion(struct Move, char pieceType) { return true; }

void ChessBoard::undo() {}

std::vector<struct Move> ChessBoard::getNextMoves() {
    std::vector<struct Move> m;
    return m;
}