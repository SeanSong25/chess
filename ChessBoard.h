#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <memory>
#include <vector>

#include "Piece.h"
#include "Player.h"
class Piece;
class ChessBoard : public std::enable_shared_from_this<ChessBoard> {
  private:
    std::vector<std::vector<Piece *>> theBoard;  // 8 x 8 chessboard

  public:
    ChessBoard();
    ~ChessBoard();
    void destroy();

    // Functions for board setup
    void defaultInit();  // Initialize standard 8 x 8 board pieces
    void setupPiece();   // Add a piece in board during setup mode
    void removePiece();  // Remove a piece in board during setup mode

    std::vector<std::vector<Piece *>> getBoard();
    std::vector<Piece *> getWhiteRooks();
    std::vector<Piece *> getBlackRooks();
    std::vector<Piece *> getWhitePawns();
    std::vector<Piece *> getBlackPawns();
    std::vector<Piece *> getWhiteKing();
    std::vector<Piece *> getBlackKing();
    std::vector<Piece *> getWhitePieces();
    std::vector<Piece *> getBlackPieces();
    void makeMove(struct Move);
    void promote(struct Move, char pieceType);
    bool checkMove(struct Move);
    bool checkPromotion(struct Move, char pieceType);
    void undo();
    std::vector<struct Move> getNextMoves();
};
#endif