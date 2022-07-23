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
            theBoard[r][c] = copyPiece(colour, pieceType, position);
        }
    }
}

Piece *ChessBoard::copyPiece(Colour col, PieceType type, Position pos) {
    if (type == KING) return new King(shared_from_this(), col, pos);
    if (type == QUEEN) return new Queen(shared_from_this(), col, pos);
    if (type == BISHOP) return new Bishop(shared_from_this(), col, pos);
    if (type == KNIGHT) return new Knight(shared_from_this(), col, pos);
    if (type == PAWN) return new Pawn(shared_from_this(), col, pos);
    if (type == ROOK) return new Rook(shared_from_this(), col, pos);
}

// ----------------------------------------------------------------------------
// Board setup methods

void ChessBoard::defaultInit() {
    // Initialize black pawns
    int row = 1;
    for (int col = 0; col < 8; col++) {
        theBoard[row][col] = new Pawn(shared_from_this(), BLACK, {row, col});
    }

    // Initialize black pawns
    row = 6;
    for (int col = 0; col < 8; col++) {
        theBoard[row][col] = new Pawn(shared_from_this(), WHITE, {row, col});
    }

    // Initialize Rooks
    theBoard[0][0] = new Rook(shared_from_this(), BLACK, {0, 0});
    theBoard[0][7] = new Rook(shared_from_this(), BLACK, {0, 7});
    theBoard[7][0] = new Rook(shared_from_this(), WHITE, {7, 0});
    theBoard[7][7] = new Rook(shared_from_this(), WHITE, {7, 7});

    // Initialize Knights
    theBoard[0][1] = new Knight(shared_from_this(), BLACK, {0, 1});
    theBoard[0][6] = new Knight(shared_from_this(), BLACK, {0, 6});
    theBoard[7][1] = new Knight(shared_from_this(), WHITE, {7, 1});
    theBoard[7][6] = new Knight(shared_from_this(), WHITE, {7, 6});

    // Initialize Bishops
    theBoard[0][2] = new Bishop(shared_from_this(), BLACK, {0, 2});
    theBoard[7][2] = new Bishop(shared_from_this(), WHITE, {7, 2});
    theBoard[0][5] = new Bishop(shared_from_this(), BLACK, {0, 5});
    theBoard[7][5] = new Bishop(shared_from_this(), WHITE, {7, 5});

    // Initialize Queens
    theBoard[0][3] = new Queen(shared_from_this(), BLACK, {0, 3});
    theBoard[7][3] = new Queen(shared_from_this(), WHITE, {7, 3});

    // Initialize Kings
    theBoard[0][4] = new King(shared_from_this(), BLACK, {0, 4});
    theBoard[7][4] = new King(shared_from_this(), WHITE, {7, 4});
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
            theBoard[r][c] = new Rook(shared_from_this(), BLACK, pos);
            break;
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
        case 'p':
            theBoard[r][c] = new Pawn(shared_from_this(), BLACK, pos);
            break;
        case 'R':
            theBoard[r][c] = new Rook(shared_from_this(), WHITE, pos);
            break;
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
        case 'P':
            theBoard[r][c] = new Pawn(shared_from_this(), WHITE, pos);
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

Piece * ChessBoard::getWhiteKing() {
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece *p = theBoard[r][c];
            if (p != nullptr && p->getPieceType() == KING && p->getColour() == WHITE) {
                return p;
            }
        }
    }
}

Piece * ChessBoard::getBlackKing() {
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece *p = theBoard[r][c];
            if (p != nullptr && p->getPieceType() == KING && p->getColour() == BLACK) {
                return p;
            }
        }
    }
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

void ChessBoard::updatePiecesPossibleMoves(){
    for(auto &i : theBoard){
        for(auto &j : i){
            j->updatePossibleNextPos();
        }
    }
}

void ChessBoard::makeMove(Move m) {
    Position p1 = m.start;
    Position p2 = m.end;
    Piece* temp = theBoard[p1.row][p1.col];
    if(temp->getPieceType() == PAWN){
        temp->checkEnPassant(p2);
    }
    if(theBoard[p2.row][p2.col] == nullptr){
        theBoard[p2.row][p2.col] = temp;
    }else{
        delete theBoard[p2.row][p2.col];
        theBoard[p2.row][p2.col] = temp;
        //if the final position has a piece, delete the original piece
        //and place the new piece
    }

    
    updatePiecesPossibleMoves();
    cout<<theBoard[p2.row][p2.col]->getPieceType()<<endl;
    //testing the piecetype of that final psoition
}
void ChessBoard::setPiece(Piece* p, Position pos){
    int row = pos.row;
    int col = pos.col;
    theBoard[row][col] = p;
}
//after checking the promotion is valid, move our pawn to the position and convert to pieceType
void ChessBoard::promote(Move m, char pieceType) {
    Position startPos = m.start;
    Position endPos = m.end;
    Piece* p = theBoard[startPos.row][startPos.col];
    Colour col = p->getColour();
    if(theBoard[endPos.row][endPos.col] != nullptr){
        delete theBoard[endPos.row][endPos.col];
    }
    if(pieceType == 'R'){
        theBoard[endPos.row][endPos.col] = new Rook(shared_from_this(), col, endPos);
    }
    else if(pieceType == 'Q'){
        theBoard[endPos.row][endPos.col] = new Queen(shared_from_this(), col, endPos);
    }
    else if(pieceType == 'K'){
        theBoard[endPos.row][endPos.col] = new Knight(shared_from_this(), col, endPos);
    }
    else if(pieceType == 'B'){
        theBoard[endPos.row][endPos.col] = new Bishop(shared_from_this(), col, endPos);
    }
    theBoard[startPos.row][startPos.col] = nullptr;
    delete p;
}

bool ChessBoard::checkMove(Move m) { 
    Position startPos = m.start;
    Position endPos = m.end;
    Piece* p = theBoard[startPos.row][startPos.col];
    if(p->isMoveValid(endPos)){
        return true;
    }
    return false;
}


//check if the promotion move is valid
bool ChessBoard::checkPromotion(Move m, char pieceType) { 
    Position startPos = m.start;
    Position endPos = m.end;
    Piece* p = theBoard[startPos.row][startPos.col];
    if(!checkMove(m) || p->getPieceType() != PAWN){
        //if invalid move or not a pawn return false
        return false;
    }
    //if the end position is not on the end of the board(row 0 for black, row 7 for white)
    if(p->getColour() == WHITE && endPos.row != 7){
        return false;
    }

    if(p->getColour() == BLACK && endPos.row != 0){
        return false;
    }
    return true;

}

void ChessBoard::undo() {}

std::vector<Move> ChessBoard::getNextMoves() {
    std::vector<Move> nextMoves;
    for(auto& i : theBoard){
        for(auto& j : i){
            std::vector<Position> tempPiecePosition = j->getPossibleNextPos();
            Position startPos = j->getPosition();
            for(auto &j : tempPiecePosition){
                Move move{startPos, j};
                nextMoves.emplace_back(move);
            }
        }
    }
    return nextMoves;
}

std::vector<Move> ChessBoard::getCaptureMoves() {
    std::vector<Move> nextCaptures;
    for(auto& i : theBoard){
        for(auto& j : i){
            std::vector<Position> tempPiecePosition = j->getPossibleCaptures();
            Position startPos = j->getPosition();
            for(auto &j : tempPiecePosition){
                Move move{startPos, j};
                nextCaptures.emplace_back(move);
            }
        }
    }
    return nextCaptures;
}