#include "Rook.h"

// constructor
Rook::Rook(std::shared_ptr<ChessBoard> board, Colour colour, Position position): 
    Piece{board, colour, position, PieceType::ROOK} {}

// copy constructor
Rook::Rook(Rook &r) {
    board = r.board;
    colour = r.getColour();
    position = r.getPosition();
    pieceType = r.getPieceType();
    firstMove = r.isFirstMove();
    possibleNextPos = r.getPossibleNextPos();
    possibleCaptures = r.getPossibleCaptures();
}

// update possible next positions and possible next captures for Rook
void Rook::updatePossibleNextPos() {
    // clear all previous data
    possibleNextPos.clear();
    possibleCaptures.clear();

    // top
    int currRow = position.row;
    int currCol = position.col;
    while(currRow >= 1) {
        if (board -> getBoard()[--currRow][currCol]) {
            if (board -> getBoard()[currRow][currCol] -> getColour() != colour) {
                possibleNextPos.emplace_back(currRow, currCol);
                possibleCaptures.emplace_back(currRow, currCol); 
            } 
            break;
        } else {
           possibleNextPos.emplace_back(currRow, currCol); 
        }
    }

    // bottom
    currRow = position.row;
    currCol = position.col;
    while(currRow <= 6) {
        if (board -> getBoard()[++currRow][currCol]) {
            if (board -> getBoard()[currRow][currCol] -> getColour() != colour) {
                possibleNextPos.emplace_back(currRow, currCol);
                possibleCaptures.emplace_back(currRow, currCol); 
            } 
            break;
        } else {
           possibleNextPos.emplace_back(currRow, currCol); 
        }
    }

    // left
    currRow = position.row;
    currCol = position.col;
    while(currCol >= 1) {
        if (board -> getBoard()[currRow][--currCol]) {
            if (board -> getBoard()[currRow][currCol] -> getColour() != colour) {
                possibleNextPos.emplace_back(currRow, currCol);
                possibleCaptures.emplace_back(currRow, currCol); 
            } 
            break;
        } else {
           possibleNextPos.emplace_back(currRow, currCol); 
        }
    }

    // right
    currRow = position.row;
    currCol = position.col;
    while(currCol <= 6) {  
        if (board -> getBoard()[currRow][++currCol]) {
            if (board -> getBoard()[currRow][currCol] -> getColour() != colour) {
                possibleNextPos.emplace_back(currRow, currCol);
                possibleCaptures.emplace_back(currRow, currCol); 
            } 
            break;
        } else {
           possibleNextPos.emplace_back(currRow, currCol); 
        }
    }
}

Rook *Rook::clone() {
    return new Rook(*this);
}

// destructor
Rook::~Rook() {}

// ----- Unit test ------
// void test_function(Piece *test_Piece, Position test_Pos, std::shared_ptr<ChessBoard> test_board) {
//     test_Piece -> updatePossibleNextPos();
//     std::vector<Position> nextMoves = test_Piece->getPossibleNextPos();
//     std::vector<Position> captureMoves = test_Piece->getPossibleCaptures();
//     // validate moves

//     // Print result
//     std::cerr << "Test valid moves for piece position at " << test_Pos.row << " " << test_Pos.col << ":" << std::endl;
//     for (const auto &[row, col] : nextMoves) {
//         std::cerr << "row: " << row << "  col: " << col << std::endl;
//     }

//     std::cerr << "Test valid captures for piece position at " << test_Pos.row << " " << test_Pos.col << ":" << std::endl;
//     for (const auto &[row, col] : captureMoves) {
//         std::cerr << "row: " << row << "  col: " << col << std::endl;
//     }
// }

// int main(void) {
//     // Change here
//     Position test_Pos{0, 0};
//     ChessBoard ch{};
//     std::shared_ptr<ChessBoard> board = std::make_shared<ChessBoard>(ch);
//     //test 1:
//     Piece *test_piece = new Rook(board, WHITE, test_Pos);
//     board -> setPiece(test_piece,test_Pos);

//     //test 2:
//     Position test_Pos_Two{3,3};
//     Piece *test_piece_Two = new Rook(board, BLACK, test_Pos_Two);
//     board -> setPiece(test_piece_Two,test_Pos_Two);

//     //test 3:
//     Position test_Pos_Three{2,2};
//     Piece *test_piece_Three =new Rook(board, WHITE, test_Pos_Three);
//     board -> setPiece(test_piece_Three,test_Pos_Three);

//     //test 4:
//     Position test_Pos_Four{3,4};
//     Piece *test_piece_Four =new Rook(board, WHITE, test_Pos_Four);
//     board -> setPiece(test_piece_Four,test_Pos_Four);

//     //test 5:
//     Position test_Pos_Five{4,2};
//     Piece *test_piece_Five =new Rook(board, BLACK, test_Pos_Five);
//     board -> setPiece(test_piece_Five,test_Pos_Five);

//     //test 6:
//     Position test_Pos_Six{5,1};
//     Piece *test_piece_Six =new Rook(board, WHITE, test_Pos_Six);
//     board -> setPiece(test_piece_Six,test_Pos_Six);

//     test_function(test_piece, test_Pos, board);
//     test_function(test_piece_Two, test_Pos_Two, board);
//     test_function(test_piece_Three, test_Pos_Three, board);
//     test_function(test_piece_Four, test_Pos_Four, board);
//     test_function(test_piece_Five, test_Pos_Five, board);
//     test_function(test_piece_Six, test_Pos_Six, board);
// }
