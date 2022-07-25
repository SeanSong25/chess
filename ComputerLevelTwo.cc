#include "ComputerLevelTwo.h"
#include "ChessBoard.h"
using namespace std;
ComputerLevelTwo::ComputerLevelTwo(Colour col){
    colour = col;
}

void ComputerLevelTwo::setBoard(ChessBoard* board){
    this->board = board;
}

struct Move ComputerLevelTwo::decideNextMove(){
    vector<Move> nextMoves;
    vector<Move> validNextMoves;
    vector<Move> captureMoves;
    vector<Move> validCaptureMoves;
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
    
    
    int moveIndex = 0;
    Position tempPosition{-1,-1};
    Move decisionMove{tempPosition, tempPosition};
    //if there is next moves
    if(validNextMoves.size() > 0){
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

// ----- Unit test ------
// void test_function(Piece *test_Piece, Piece::Position test_Pos) {
//     // Initialize board and piece
//     Piece *testBoard[8][8];

//     // Set the board to nullptr initially
//     for (int r = 0; r < 8; r++) {
//         for (int c = 0; c < 8; c++) {
//             testBoard[r][c] = nullptr;
//         }
//     }
//     testBoard[test_Pos.row][test_Pos.col] = test_Piece;

//     // validate moves
//     test_Piece->validMoves(testBoard);
//     std::vector<Piece::Position> moves = test_Piece->getPossibleMoves();

//     // Print result
//     std::cerr << "Test valid moves for piece position at " << test_Pos.row << " " << test_Pos.col << ":" << std::endl;
//     for (const auto &[row, col] : moves) {
//         std::cerr << "row: " << row << "  col: " << col << std::endl;
//     }

//     delete test_Piece;
// }

// int main(void) {
//     // Change here
//     Piece::Position test_Pos{0, 0};
//     Piece *test_piece = new King(Piece::BLACK, test_Pos);
//     test_function(test_piece, test_Pos);
// }