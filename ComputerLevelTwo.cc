#include "ComputerLevelTwo.h"
#include "ChessBoard.h"
using namespace std;
ComputerLevelTwo::ComputerLevelTwo(Colour col){
    colour = col;
}

void ComputerLevelTwo::setBoard(shared_ptr<ChessBoard> board){
    this->board = board;
}

struct Move ComputerLevelTwo::decideNextMove(){
    vector<Move> nextMoves;
    vector< Move> captureMoves;
    nextMoves = board.get()->getNextMoves(); 
    captureMoves = board.get()->getCaptureMoves();
    //get all possible moves from the possible moves of the board
    
    int moveIndex = 0;
    Position tempPosition{-1,-1};
    Move decisionMove{tempPosition, tempPosition};
    if(nextMoves.size() == 0){
        if(captureMoves.size()>0){
        //if there is capture move then pick a capture move randomly
        int index = rand()%captureMoves.size();
        decisionMove = captureMoves[index];
        }
        else{
            int index = rand()%nextMoves.size();
            decisionMove = nextMoves[index];
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