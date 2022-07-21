#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <vector>

#include "Piece.h"
#include "utils.h"

class Piece;

class ChessBoard {
  private:
    std::vector<std::vector<Piece *>> theBoard;

  public:
    std::vector<std::vector<Piece *>> getBoard();
    std::vector<Piece *> getWhiteRooks();  // first rook should be the one to the left
    std::vector<Piece *> getBlackRooks();
    std::vector<Piece *> getWhiteKing();
    std::vector<Piece *> getBlackKing();
    std::vector<Piece *> getWhitePieces();
    std::vector<Piece *> getBlackPieces();
};

#endif