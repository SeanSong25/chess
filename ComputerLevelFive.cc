#include "ComputerLevelFive.h"
#include "ChessBoard.h"
#include <limits>

/*
a chess AI implemented using minmax search and alpha beta pruning,
use a scoring system and search 3 steps ahead to find the most optimal move
*/

/*-------------------------------------- Node ---------------------------------------------*/
// constructor
Node::Node(ChessBoard *b, Move m): chessBoard{b}, children{}, move{m} {} 

// destorys the tree
void Node::destroy(Node *parent) {
    if (parent -> children.size() == 0) {
        delete parent -> chessBoard;
    } else {
        for (auto &child : parent -> children) {
            destroy(child);
        }
        delete parent -> chessBoard;
    }
}

// destructor
Node::~Node() {
    for (auto &child : children) {
        destroy(child);
    }
    chessBoard = nullptr;
}

/*-------------------------------------- ComputerLevelFive --------------------------------*/
// constructor
ComputerLevelFive::ComputerLevelFive(Colour c): root{}, bestMove{Move{{-1, -1}, {-1, -1}}} {
    colour = c;
} 

// destructor
ComputerLevelFive::~ComputerLevelFive() {
    delete root;
}

// return the score of a piece
int ComputerLevelFive::getPieceScore(PieceType type) {
    if (type == PieceType::PAWN) {
        return 1;
    } else if (type == PieceType::KNIGHT) {
        return 3;
    } else if (type == PieceType::BISHOP) {
        return 3;
    } else if (type == PieceType::ROOK) {
        return 5;
    } else if (type == PieceType::QUEEN) {
        return 9;
    } else {
        return 15;
    }
    return 0;
}

// calculate the score of a board
int ComputerLevelFive::calculateScore(std::vector<std::vector<Piece *>> b, Colour c) {
    int whiteScore = 0;
    int blackScore = 0;
    for (auto &row : b) {
        for (auto &piece: row) {
            if (piece) {
                if (piece -> getColour() == WHITE) {
                    whiteScore += getPieceScore(piece -> getPieceType());
                } else {
                    blackScore += getPieceScore(piece -> getPieceType());
                }
            }
        }
    }
    if (c == WHITE) {
        return whiteScore - blackScore;
    } else {
        return blackScore - whiteScore;
    }
}



// find move that gives maximum score of a board disregarding opponent move
int ComputerLevelFive::minimax(int depth, Node *parent, bool max, Colour c, int alpha, int beta) {
    if (depth == 0) {
        return calculateScore(parent -> chessBoard -> getBoard(), c);
    }

    if (max) {
        int max = -99999;
        for (auto &child : parent -> children) {
            int score = minimax(depth - 1, child, false, c, alpha, beta);
            if (max < score) {
                max = score;
                if (parent == root) {
                    bestMove = child -> move;
                }
            }
            if (alpha < score) {
                alpha = score;
            }
            if (beta <= alpha) {
                break;
            }
        }
        return max;
    } else {
        int min = 99999;
        for (auto &child : parent -> children) {
            int score = minimax(depth - 1, child, true, c, alpha, beta);
            if (score < min) {
                min = score;
            }
            if (score < beta) {
                beta = score;
            }
            if (beta <= alpha) {
                break;
            }
        }
        return min;
    }
    return 0;
}

void ComputerLevelFive::buildTree(int depth, Node *parent, Colour c) {
    ChessBoard *currBoard = parent -> chessBoard;
    if (depth == 0) {
        return;
    }

    // get all possible next moves
    std::vector<Move> possibleNextMoves;
    for (auto &move : currBoard -> getNextMoves(c)) {
        if (currBoard -> checkMove(move, c)) {
            possibleNextMoves.emplace_back(move);
        }
    }

    // insert all possible moves
    for (auto &move : possibleNextMoves) {
        ChessBoard *newBoard = new ChessBoard(*currBoard);
        newBoard -> makeMove(move);
        Node *newNode = new Node(newBoard, move);
        parent -> children.emplace_back(newNode);
        Colour newColour = Colour::BLACK;
        if (c == Colour::BLACK) {
            newColour = Colour::WHITE;
        }
        // recursively build the tree
        buildTree(depth - 1, newNode, newColour);
    }
}

void ComputerLevelFive::printTree(Node *parent) {
    if (parent->children.size() == 0) return;
    for (auto &child : parent -> children) {
        std::cout << "myself" << std::endl;
        child->chessBoard->print();
        std::cout << "my children: " << child -> children.size() << std::endl;
        printTree(child);
    }
}

Move ComputerLevelFive::decideNextMove() {
    // build min max tree
    root = new Node(board, Move{{-1, -1}, {-1, -1}});
    buildTree(3, root, colour);

    //set default best move
    bestMove = root -> children[0] -> move;

    minimax(3, root, true, colour, -99999, 99999);

    // delete tree
    delete root;
    
    return bestMove;
}

