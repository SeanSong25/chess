#include "ChessBoard.h"

#include <assert.h>

#include <algorithm>
#include <iostream>
#include <utility>

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
// Constructor and destructor

ChessBoard::ChessBoard() {
    // Construct 8 x 8 chessboard
    theBoard = vector<vector<Piece *>>(8, vector<Piece *>(8, nullptr));
}

void ChessBoard::destroy() {
    for (int r = 0; r < theBoard.size(); ++r) {
        for (int c = 0; c < theBoard[0].size(); ++c) {
            if (theBoard[r][c]) {
                delete theBoard[r][c];
                theBoard[r][c] = nullptr;
            }
        }
    }
}
ChessBoard::~ChessBoard() {
    destroy();
}

ChessBoard::ChessBoard(const ChessBoard &o) {
    theBoard = vector<vector<Piece *>>(8, vector<Piece *>(8, nullptr));
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (o.theBoard[r][c] == nullptr) continue;
            Colour colour = o.theBoard[r][c]->getColour();
            PieceType pieceType = o.theBoard[r][c]->getPieceType();
            Position position = o.theBoard[r][c]->getPosition();
            bool firstMove = o.theBoard[r][c]->isFirstMove();
            bool enPassant = o.theBoard[r][c]->isEnPassant();
            Piece *enPassantPiece = o.theBoard[r][c] -> getEnPassantPiece();
            Position enPassantPosition = o.theBoard[r][c] -> getEnPassantPosition();
            theBoard[r][c] = copyPiece(colour, pieceType, position,
             firstMove, enPassant, enPassantPiece, enPassantPosition);
        }
    }
}

Piece *ChessBoard::copyPiece(Colour col, PieceType type, Position pos,
    bool firstMove, bool enPassant, Piece *enPassantPiece, Position enPassantPosition) {
    if (type == KING) {
        Piece * p = new King(this, col, pos);
        p->setFirstMove(firstMove);
        p->setEnPassant(enPassant, enPassantPiece, enPassantPosition);
        return p;
    } 
    if (type == QUEEN) {
        Piece * p = new Queen(this, col, pos);
        p->setFirstMove(firstMove);
        p->setEnPassant(enPassant, enPassantPiece, enPassantPosition);
        return p;
    }
    if (type == BISHOP) {
        Piece * p = new Bishop(this, col, pos);
        p->setFirstMove(firstMove);
        p->setEnPassant(enPassant, enPassantPiece, enPassantPosition);
        return p;
    }
    if (type == KNIGHT) {
        Piece * p = new Knight(this, col, pos);
        p->setFirstMove(firstMove);
        p->setEnPassant(enPassant, enPassantPiece, enPassantPosition);
        return p;
    }
    if (type == PAWN) {
        Piece * p = new Pawn(this, col, pos);
        p->setFirstMove(firstMove);
        p->setEnPassant(enPassant, enPassantPiece, enPassantPosition);
        return p;
    }
    if (type == ROOK) {
        Piece * p = new Rook(this, col, pos);
        p->setFirstMove(firstMove);
        p->setEnPassant(enPassant, enPassantPiece, enPassantPosition);
        return p;
    }
    return nullptr;
}

// ----------------------------------------------------------------------------
// Board setup methods

void ChessBoard::defaultInit() {
    // Initialize black pawns
    int row = 1;
    for (int col = 0; col < 8; col++) {
        theBoard[row][col] = new Pawn(this, BLACK, {row, col});
    }

    // Initialize black pawns
    row = 6;
    for (int col = 0; col < 8; col++) {
        theBoard[row][col] = new Pawn(this, WHITE, {row, col});
    }

    // Initialize Rooks
    theBoard[0][0] = new Rook(this, BLACK, {0, 0});
    theBoard[0][7] = new Rook(this, BLACK, {0, 7});
    theBoard[7][0] = new Rook(this, WHITE, {7, 0});
    theBoard[7][7] = new Rook(this, WHITE, {7, 7});

    // Initialize Knights
    theBoard[0][1] = new Knight(this, BLACK, {0, 1});
    theBoard[0][6] = new Knight(this, BLACK, {0, 6});
    theBoard[7][1] = new Knight(this, WHITE, {7, 1});
    theBoard[7][6] = new Knight(this, WHITE, {7, 6});

    // Initialize Bishops
    theBoard[0][2] = new Bishop(this, BLACK, {0, 2});
    theBoard[7][2] = new Bishop(this, WHITE, {7, 2});
    theBoard[0][5] = new Bishop(this, BLACK, {0, 5});
    theBoard[7][5] = new Bishop(this, WHITE, {7, 5});

    // Initialize Queens
    theBoard[0][3] = new Queen(this, BLACK, {0, 3});
    theBoard[7][3] = new Queen(this, WHITE, {7, 3});

    // Initialize Kings
    theBoard[0][4] = new King(this, BLACK, {0, 4});
    theBoard[7][4] = new King(this, WHITE, {7, 4});
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
        case 'r':
            theBoard[r][c] = new Rook(this, BLACK, pos);
            break;
        case 'n':
            theBoard[r][c] = new Knight(this, BLACK, pos);
            break;
        case 'b':
            theBoard[r][c] = new Bishop(this, BLACK, pos);
            break;
        case 'q':
            theBoard[r][c] = new Queen(this, BLACK, pos);
            break;
        case 'k':
            theBoard[r][c] = new King(this, BLACK, pos);
            break;
        case 'p':
            theBoard[r][c] = new Pawn(this, BLACK, pos);
            break;
        case 'R':
            theBoard[r][c] = new Rook(this, WHITE, pos);
            break;
        case 'N':
            theBoard[r][c] = new Knight(this, WHITE, pos);
            break;
        case 'B':
            theBoard[r][c] = new Bishop(this, WHITE, pos);
            break;
        case 'Q':
            theBoard[r][c] = new Queen(this, WHITE, pos);
            break;
        case 'K':
            theBoard[r][c] = new King(this, WHITE, pos);
            break;
        case 'P':
            theBoard[r][c] = new Pawn(this, WHITE, pos);
            break;
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

vector<Piece *> ChessBoard::getWhiteRooks() {
    vector<Piece *> whiteRooks{};

    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece *p = theBoard[r][c];
            if (p != nullptr && p->getPieceType() == ROOK && p->getColour() == WHITE) {
                whiteRooks.emplace_back(p);
            }
        }
    }
    return whiteRooks;
}

vector<Piece *> ChessBoard::getBlackRooks() {
    vector<Piece *> blackRooks{};

    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece *p = theBoard[r][c];
            if (p != nullptr && p->getPieceType() == ROOK && p->getColour() == BLACK) {
                blackRooks.emplace_back(p);
            }
        }
    }
    return blackRooks;
}

vector<Piece *> ChessBoard::getWhitePawns() {
    vector<Piece *> whitePawns{};

    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece *p = theBoard[r][c];
            if (p != nullptr && p->getPieceType() == PAWN && p->getColour() == WHITE) {
                whitePawns.emplace_back(p);
            }
        }
    }
    return whitePawns;
}

vector<Piece *> ChessBoard::getBlackPawns() {
    vector<Piece *> blackPawns{};

    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece *p = theBoard[r][c];
            if (p != nullptr && p->getPieceType() == PAWN && p->getColour() == BLACK) {
                blackPawns.emplace_back(p);
            }
        }
    }
    return blackPawns;
}

Piece *ChessBoard::getWhiteKing() {
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece *p = theBoard[r][c];
            if (p != nullptr && p->getPieceType() == KING && p->getColour() == WHITE) {
                return p;
            }
        }
    }
    return nullptr;
}

Piece *ChessBoard::getBlackKing() {
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece *p = theBoard[r][c];
            if (p != nullptr && p->getPieceType() == KING && p->getColour() == BLACK) {
                return p;
            }
        }
    }
    return nullptr;
}

vector<Piece *> ChessBoard::getWhitePieces() {
    vector<Piece *> whitePieces{};

    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece *p = theBoard[r][c];
            if (p != nullptr && p->getColour() == WHITE) {
                whitePieces.emplace_back(p);
            }
        }
    }
    return whitePieces;
}

vector<Piece *> ChessBoard::getBlackPieces() {
    vector<Piece *> blackPieces{};

    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece *p = theBoard[r][c];
            if (p != nullptr && p->getColour() == BLACK) {
                blackPieces.emplace_back(p);
            }
        }
    }
    return blackPieces;
}

// ----------------------------------------------------------------------------
// Game Logic

void ChessBoard::updatePiecesPossibleMoves() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (theBoard[i][j]) {
                theBoard[i][j]->updatePossibleNextPos();
            }
        }
    }
}

// make move according to the move passed in
void ChessBoard::makeMove(Move m) {
    Position p1 = m.start;
    Position p2 = m.end;
    Piece *temp = theBoard[p1.row][p1.col];

    if (temp->getPieceType() == PAWN) {
        if (temp->isEnPassant()) {
            if (p2 == temp->getEnPassantPosition()) {
                Piece *p = temp->getEnPassantPiece();
                Position enPassantOrigin = p->getPosition();
                theBoard[enPassantOrigin.row][enPassantOrigin.col] = nullptr;
            }
        } else {
            temp->checkEnPassant(p2);
        }
    }

    if (theBoard[p2.row][p2.col]) {
        delete theBoard[p2.row][p2.col];
    }
    theBoard[p2.row][p2.col] = temp;
    theBoard[p1.row][p1.col] = nullptr;

    // update piece position
    temp->setPosition(p2);

    temp->afterMove();
    updatePiecesPossibleMoves();

    for (auto &i : theBoard) {
        for (auto &j : i) {
            if (j != nullptr && j->getColour() == temp->getColour()) {
                Position p{};
                j->setEnPassant(false, nullptr, p);
            }
        }
    }

    // if the moved piece is a king and moves 2 columns, then we can make a move
    // using the rook in the castling
    if (temp->getPieceType() == KING && abs(p2.col - p1.col) == 2) {
        if (p2.col < p1.col) {
            Move rookMove{{p1.row, p1.col - 4}, {p1.row, p1.col - 1}};
            makeMove(rookMove);
        } else {
            Move rookMove{{p1.row, p1.col + 3}, {p1.row, p1.col + 1}};
            makeMove(rookMove);
        }
    }
}

// set the piece p at the position pos
void ChessBoard::setPiece(Piece *p, Position pos) {
    int row = pos.row;
    int col = pos.col;
    theBoard[row][col] = p;
    p->setPosition(pos);
}

// after checking the promotion is valid, move our pawn to the position and convert to pieceType
void ChessBoard::promote(Move m, char pieceType) {
    Position startPos = m.start;
    Position endPos = m.end;
    Piece *p = theBoard[startPos.row][startPos.col];
    Colour col = p->getColour();
    if (theBoard[endPos.row][endPos.col] != nullptr) {
        delete theBoard[endPos.row][endPos.col];
    }
    if (pieceType == 'R') {
        theBoard[endPos.row][endPos.col] = new Rook(this, col, endPos);
    } else if (pieceType == 'Q') {
        theBoard[endPos.row][endPos.col] = new Queen(this, col, endPos);
    } else if (pieceType == 'K') {
        theBoard[endPos.row][endPos.col] = new Knight(this, col, endPos);
    } else if (pieceType == 'B') {
        theBoard[endPos.row][endPos.col] = new Bishop(this, col, endPos);
    }
    theBoard[startPos.row][startPos.col] = nullptr;
    theBoard[endPos.row][endPos.col]->updatePossibleNextPos();
    delete p;
}

bool ChessBoard::checkMove(Move m, Colour colour) {
    Position startPos = m.start;
    Position endPos = m.end;
    if (startPos.row >= 0 && startPos.row <= 7 && endPos.row >= 0 && endPos.row <= 7 && startPos.col >= 0 && startPos.col <= 7 && endPos.col >= 0 && endPos.col <= 7) {
        if (theBoard[startPos.row][startPos.col]) {
            Piece *p = theBoard[startPos.row][startPos.col];
            if (p && p->isMoveValid(endPos, colour)) {
                return true;
            }
        }
    }
    return false;
}

// check if the promotion move is valid
bool ChessBoard::checkPromotion(Move m, char pieceType, Colour colour) {
    Position startPos = m.start;
    Position endPos = m.end;
    Piece *p = theBoard[startPos.row][startPos.col];
    if (!checkMove(m, colour) || p->getPieceType() != PAWN) {
        // if invalid move or not a pawn return false
        return false;
    }
    // if the end position is not on the end of the board(row 0 for black, row 7 for white)
    if (p->getColour() == WHITE && endPos.row != 0) {
        return false;
    }

    if (p->getColour() == BLACK && endPos.row != 7) {
        return false;
    }
    return true;
}

void ChessBoard::undo() {}

std::vector<Move> ChessBoard::getNextMoves(Colour clr) {
    std::vector<Move> nextMoves;
    for (auto &i : theBoard) {
        for (auto &j : i) {
            if (j && j->getColour() == clr) {
                std::vector<Position> tempPiecePosition = j->getPossibleNextPos();
                Position startPos = j->getPosition();
                for (auto &k : tempPiecePosition) {
                    Move move{startPos, k};
                    nextMoves.emplace_back(move);
                }
            }
        }
    }
    return nextMoves;
}

void ChessBoard::print() {
    for (auto &i: theBoard) {
        for (auto &j: i) {
            if (!j) {
                std::cout << " ";
            } else {
                if (j->getPieceType()==PAWN & j->getColour()==WHITE) {
                    std::cout << "P";
                } else if (j->getPieceType()==PAWN & j->getColour()==BLACK) {
                    std::cout << "p";
                } else if (j->getPieceType()==KNIGHT & j->getColour()==WHITE) {
                    std::cout << "N";
                } else if (j->getPieceType()==KNIGHT & j->getColour()==BLACK) {
                    std::cout << "n";
                } else if (j->getPieceType()==KING & j->getColour()==WHITE) {
                    std::cout << "K";
                } else if (j->getPieceType()==KING & j->getColour()==BLACK) {
                    std::cout << "k";
                } else if (j->getPieceType()==QUEEN & j->getColour()==WHITE) {
                    std::cout << "Q";
                } else if (j->getPieceType()==QUEEN & j->getColour()==BLACK) {
                    std::cout << "q";
                } else if (j->getPieceType()==BISHOP & j->getColour()==WHITE) {
                    std::cout << "B";
                } else if (j->getPieceType()==BISHOP & j->getColour()==BLACK) {
                    std::cout << "b";
                } else if (j->getPieceType()==ROOK & j->getColour()==WHITE) {
                    std::cout << "R";
                } else if (j->getPieceType()==ROOK & j->getColour()==BLACK) {
                    std::cout << "r";
                }
            }
        }
        std::cout << std::endl;
    }
}

std::vector<Move> ChessBoard::getCaptureMoves(Colour clr) {
    std::vector<Move> nextCaptures;
    for (auto &i : theBoard) {
        for (auto &j : i) {
            if (j && j->getColour() == clr) {
                std::vector<Position> tempPieceCaptures = j->getPossibleCaptures();
                Position startPos = j->getPosition();
                for (auto &k : tempPieceCaptures) {
                    Move move{startPos, k};
                    nextCaptures.emplace_back(move);
                }
            }
        }
    }
    return nextCaptures;
}
