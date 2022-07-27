#ifndef COMPUTERLEVELFIVE_H
#define COMPUTERLEVELFIVE_H
#include "ComputerPlayer.h"
#include "Piece.h"

class Node {
    ChessBoard *chessBoard;
    Move move;
    std::vector<Node *> children;
    Node(ChessBoard *, Move);
    ~Node();
    void destroy(Node *);

    friend class ComputerLevelFive;
};

class ComputerLevelFive : public ComputerPlayer {
    private:
        Node *root;
        Move bestMove;
        Move decideNextMove() override;
        int getPieceScore(PieceType);
        int calculateScore(std::vector<std::vector<Piece *>>, Colour);
        int minimax(int, Node *, bool, Colour, int, int);
        void buildTree(int, Node *, Colour);
        void printTree(Node *);
    public:
        ComputerLevelFive(Colour);
        ~ComputerLevelFive();
        void setBoard(ChessBoard *);
};

#endif