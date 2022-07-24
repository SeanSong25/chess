#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <memory>
#include <vector>

#include "Piece.h"
#include "Player.h"
class Piece;
class ChessBoard{
  private:
    std::vector<std::vector<Piece *>> theBoard;  // 8 x 8 chessboard
    Piece *copyPiece(Colour, PieceType, Position);

  public:
    ChessBoard();
    ~ChessBoard();
    void destroy();

    // Functions for board setup
    void defaultInit();  // Initialize standard 8 x 8 board pieces
    void setupPiece();   // Add a piece in board during setup mode
    void removePiece();  // Remove a piece in board during setup mode

    // Copy Ctor
    // Usage: shared_ptr<ChessBoard> temp = make_shared<ChessBoard>(*board);
    ChessBoard(const ChessBoard &);

    std::vector<std::vector<Piece *>> getBoard();
    std::vector<Piece *> getWhiteRooks();
    std::vector<Piece *> getBlackRooks();
    std::vector<Piece *> getWhitePawns();
    std::vector<Piece *> getBlackPawns();
    Piece * getWhiteKing();
    Piece * getBlackKing();
    std::vector<Piece *> getWhitePieces();
    std::vector<Piece *> getBlackPieces();
    void setPiece(Piece* p, Position pos);
    void makeMove(Move);
    void promote(Move, char pieceType);
    bool checkMove(Move);
    bool checkPromotion(Move, char pieceType);
    void undo();
    std::vector<Move> getNextMoves();
    std::vector<Move> getCaptureMoves();

    void updatePiecesPossibleMoves(Colour col);
};
#endif