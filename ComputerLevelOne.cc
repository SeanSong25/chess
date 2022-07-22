#include "ComputerLevelOne.h"
#include "ChessBoard.h"
using namespace std;
ComputerLevelOne::ComputerLevelOne(Colour col){
    colour = col;
}

void ComputerLevelOne::setBoard(shared_ptr<ChessBoard> board){
    this->board = board;
}

struct Move ComputerLevelOne::decideNextMove(){
    vector<struct Move> nextMoves;
    nextMoves = board.get()->getNextMoves(); 
    //get all possible moves from the possible moves of the board
    
    int moveIndex = 0;
    Position tempPosition{-1,-1};
    Move decisionMove{tempPosition, tempPosition};
    //default decision Move to -1, -1 so when returned to makeMpve, it fails and return false
    vector<struct Move> validMoves;
    //contains all the valid moves
    for(auto i : nextMoves){
        if(board.get()->checkMove(i)){
            validMoves.emplace_back(i);
        }
    }

    if(validMoves.size() == 0){
        return decisionMove; //if there is no valid moves return -1, -1
    }

    moveIndex = rand()%validMoves.size(); //find a random position in the valid moves array
    decisionMove = validMoves[moveIndex];
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