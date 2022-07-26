#include "ComputerLevelFive.h"
#include "ChessBoard.h"
#include <unordered_map>
using namespace std;
ComputerLevelFive::ComputerLevelFive(Colour col){
    colour = col;
}

void ComputerLevelFive::setBoard(ChessBoard* board){
    this->board = board;
}

//find out if after making this move, our piece can capture an opponent piece in
//one move
bool ComputerLevelFive::canCaptureEnemyPiece(Move m){
    ChessBoard* newBoard = new ChessBoard(*board);
    Piece* ourPiece = newBoard->getBoard()[m.start.row][m.start.col];
    ChessBoard* tempStoreBoard = board;
    board = newBoard;
    for (auto &i : board -> getBoard()) {
        for (auto &j: i) {
            if(j){
                j -> updatePossibleNextPos();
            }
        }
    }
    board->makeMove(m);
    ourPiece -> updatePossibleNextPos();
    vector<Position> possibleCaptures = ourPiece->getPossibleCaptures();
    board = tempStoreBoard;
    if(possibleCaptures.size() > 0){
        delete newBoard;
        return true;
    }
    delete newBoard;
    return false;
}

struct Move ComputerLevelFive::decideNextMove(){
    vector<Move> nextMoves;
    vector<Move> validNextMoves;
    vector<Move> captureMoves;
    vector<Move> validCaptureMoves;
    vector<Move> opponentPossibleMoves;
    vector<Move> opponentValidPossibleMoves;
    vector<Move> opponentCaptureMoves;
    vector<Move> opponentValidCaptureMoves;
    vector<Piece* > ourPieces;

    unordered_map<PieceType, int> priority_map;
    
    priority_map[KING] = 7;
    priority_map[QUEEN] = 6;
    priority_map[BISHOP] = 5;
    priority_map[KNIGHT] = 5;
    priority_map[ROOK] = 5;
    priority_map[PAWN] = 1;

    nextMoves = board->getNextMoves(getColour());
    //loop through next moves to find valid next moves
    for(int i = 0; i<nextMoves.size();i++){
        if(board->checkMove(nextMoves[i], getColour())){
            validNextMoves.emplace_back(nextMoves[i]);
        }
    }

    captureMoves = board->getCaptureMoves(getColour());
    //loop through capture moves to find valid capture moves
    for(int i = 0; i<captureMoves.size();i++){
        if(board->checkMove(captureMoves[i], getColour())){
            validCaptureMoves.emplace_back(captureMoves[i]);
        }
    }
    //update opponent possible moves, then find all opponent capture moves and possible moves
    
    if(getColour() == WHITE){
        board->updatePiecesPossibleMoves();
        opponentCaptureMoves = board->getCaptureMoves(BLACK);
        for(int i = 0; i<opponentCaptureMoves.size(); i++){
            if(board->checkMove(opponentCaptureMoves[i], BLACK)){
                opponentValidCaptureMoves.push_back(opponentCaptureMoves[i]);
            }
        }
        opponentPossibleMoves = board->getNextMoves(BLACK);
        for(int i = 0; i<opponentPossibleMoves.size(); i++){
            if(board->checkMove(opponentPossibleMoves[i], BLACK)){
                opponentValidPossibleMoves.push_back(opponentPossibleMoves[i]);
            }
        }
        ourPieces = board->getWhitePieces();
    }else{
        board->updatePiecesPossibleMoves();
        opponentCaptureMoves = board->getCaptureMoves(WHITE);
        for(int i = 0; i<opponentCaptureMoves.size(); i++){
            if(board->checkMove(opponentCaptureMoves[i], WHITE)){
                opponentValidCaptureMoves.push_back(opponentCaptureMoves[i]);
            }
        }
        opponentPossibleMoves = board->getNextMoves(WHITE);
        for(int i = 0; i<opponentPossibleMoves.size(); i++){
            if(board->checkMove(opponentPossibleMoves[i], WHITE)){
                opponentValidPossibleMoves.push_back(opponentPossibleMoves[i]);
            }
        }
        ourPieces = board->getBlackPieces();
    }

    int moveIndex = 0;
    Position tempPosition{-1,-1};
    Move decisionMove{tempPosition, tempPosition};
    //loop through our piece and find a piece that has its position on
    //a possible capture position of opponent pieces

    if(validNextMoves.size() > 0){
        for(int i = 0; i<ourPieces.size(); i++){
        Position p = ourPieces[i]->getPosition();
        for(int j = 0; j<opponentValidCaptureMoves.size(); j++){

            Position endPos = opponentValidCaptureMoves[j].end;
            if(endPos == p){
                Position opponentStart = opponentValidCaptureMoves[j].start;
                //find if there is any of our capture moves that capture this attacking piece
                //if there is, capture it
                for(int m = 0; m<validCaptureMoves.size(); m++){
                    if(validCaptureMoves[m].end.row == opponentStart.row && validCaptureMoves[m].end.col == opponentStart.col){
                        return validCaptureMoves[m];
                    }
                }

                //find out if we can capture another piece with an equivalent or higher priority,
                //if we can, trade it

                for(int m = 0; m<validCaptureMoves.size(); m++){
                    Position captureablePosition = validCaptureMoves[m].end;
                    Piece* captureablePiece = board->getBoard()[captureablePosition.row][captureablePosition.col];
                    if(priority_map[captureablePiece->getPieceType()] >= priority_map[ourPieces[i]->getPieceType()]){
                        return validCaptureMoves[m];
                    }
                }

                //find the next positions our to-be captured piece can go to
                //if there are such positions, find if there exists one that we can go to
                // and there are no possible captures by opponent pieces on that new position
                vector<Position> nextPositions = ourPieces[i] -> getPossibleNextPos();
                if(nextPositions.size() > 0){
                    for(int k = 0; k<nextPositions.size(); k++){
                        Position myNextPosition = nextPositions[k];
                        bool flag = true;
                        for(int l = 0; l<opponentValidPossibleMoves.size(); l++){

                            if(opponentValidPossibleMoves[l].end == myNextPosition){
                                flag = false;
                                break;
                            }
                        }
                        if(flag){
                            decisionMove = Move{p, myNextPosition};
                            if(board->checkMove(decisionMove, getColour())){
                                return decisionMove;
                            }
                        }
                    }
                }
            }
        }
    }
        if(validCaptureMoves.size()>0){
            //find a capture move that captures the most valuable piece
            int maxPriority = 1;
            decisionMove = validCaptureMoves[0];
            for(auto &i : validCaptureMoves){
                Piece* capturable = board->getBoard()[i.end.row][i.end.col];
                if(priority_map[capturable->getPieceType()] > maxPriority){
                    maxPriority = priority_map[capturable->getPieceType()];
                    decisionMove = i;
                }
            }
        }
        else{
            //find if a move can lead to a next capture
            decisionMove = validNextMoves[0];
            for(auto &i : validNextMoves){
                if(canCaptureEnemyPiece(i)){
                    decisionMove = i;
                }
            }
        }
    }
    return decisionMove;
}