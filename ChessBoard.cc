#include "ChessBoard.h"
#include <iostream>
using namespace std;

void ChessBoard::makeMove(Move m){
    Position p1 = m.start;
    Position p2 = m.end;
    Piece* temp = theBoard[p1.row][p1.col];
    if(theBoard[p2.row][p2.col] == nullptr){
        theBoard[p2.row][p2.col] = temp;
    }else{
        delete theBoard[p2.row][p2.col];
        theBoard[p2.row][p2.col] = temp;
        //if the final position has a piece, delete the original piece
        //and place the new piece
    }
    cout<<theBoard[p2.row][p2.col]->getPieceType()<<endl;
    //testing the piecetype of that final psoition
}

void ChessBoard::promote(struct Move m, char pieceType){
}

void ChessBoard::setPiece(Piece* p, Position pos){
    int row = pos.row;
    int col = pos.col;
    theBoard[row][col] = p;
}
bool ChessBoard::checkMove(struct Move m){return true;}

bool ChessBoard::checkPromotion(struct Move m, char pieceType){return true;}

void ChessBoard::undo(){}

std::vector<struct Move> ChessBoard::getNextMoves(){
    std::vector<struct Move> m;
    return m;
}


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

vector<Piece *> ChessBoard::getWhiteRooks() {}
vector<Piece *> ChessBoard::getBlackRooks() {}
vector<Piece *> ChessBoard::getWhiteKing() {}
vector<Piece *> ChessBoard::getBlackKing() {}
vector<Piece *> ChessBoard::getWhitePieces() {}
vector<Piece *> ChessBoard::getBlackPieces() {}
