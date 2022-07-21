#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <vector>

#include "Piece.h"
#include "utils.h"

class Piece;

class ChessBoard {
  private:
    std::vector<std::vector<Piece *>> theBoard;  // store 8 x 8 chessboard

  public:
    ChessBoard();
    ~ChessBoard();
    void defaultInit();  // Initialize standard 8 x 8 board pieces
    std::vector<std::vector<Piece *>> getBoard();
    std::vector<Piece *> getWhiteRooks();
    std::vector<Piece *> getBlackRooks();
    std::vector<Piece *> getWhiteKing();
    std::vector<Piece *> getBlackKing();
    std::vector<Piece *> getWhitePieces();
    std::vector<Piece *> getBlackPieces();
};

#endif