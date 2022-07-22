#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "Player.h"
#include "Piece.h"
#include <vector>
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
    void makeMove(struct Move);
    void promote(struct Move, char pieceType);
    bool checkMove(struct Move);
    void setPiece(Piece* p, Position pos);
    bool checkPromotion(struct Move, char pieceType);
    void undo();
    std::vector<struct Move> getNextMoves();
};
#endif