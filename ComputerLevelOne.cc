#include "ComputerLevelOne.h"
#include "ChessBoard.h"
using namespace std;
ComputerLevelOne::ComputerLevelOne(Colour col){
    colour = col;
}

void ComputerLevelOne::setBoard(shared_ptr<ChessBoard> board){
    this->board = board;
}

struct Move ComputerLevelOne::computeNextMove(){
    vector<struct Move> nextMoves;
    nextMoves = board.get()->getNextMoves();
    
    int moveIndex = 0;
    Position tempPosition{0,0};
    Move decisionMove{tempPosition, tempPosition};
    if(nextMoves.size() == 1){
        decisionMove = nextMoves[0];
        board.get()->makeMove(decisionMove);
    }
    else{
        moveIndex = rand()%nextMoves.size();
        decisionMove = nextMoves[moveIndex];
        board.get()->makeMove(decisionMove);
        
    }
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