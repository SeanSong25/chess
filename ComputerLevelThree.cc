#include "ComputerLevelThree.h"
#include "ChessBoard.h"
using namespace std;
ComputerLevelThree::ComputerLevelThree(Colour col){
    colour = col;
}

void ComputerLevelThree::setBoard(ChessBoard* board){
    this->board = board;
}

struct Move ComputerLevelThree::decideNextMove(){
    vector<Move> nextMoves;
    vector<Move> validNextMoves;
    vector<Move> captureMoves;
    vector<Move> validCaptureMoves;
    vector<Move> opponentPossibleMoves;
    vector<Move> opponentValidPossibleMoves;
    vector<Move> opponentCaptureMoves;
    vector<Move> opponentValidCaptureMoves;
    vector<Piece* > ourPieces;

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
        board->updatePiecesPossibleMoves(BLACK);
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
        board->updatePiecesPossibleMoves(WHITE);
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
        //if there is capture move then pick a capture move randomly
            int index = rand()%validCaptureMoves.size();
            decisionMove = validCaptureMoves[index];
        }
        else{
            int index = rand()%validNextMoves.size();
            decisionMove = validNextMoves[index];
        }
    }
    return decisionMove;
}