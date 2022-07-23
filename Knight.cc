#include "Knight.h"

// constructor
Knight::Knight(std::shared_ptr<ChessBoard> board, Colour colour, Position position): 
    Piece{board, colour, position, PieceType::KNIGHT} {}

// copy constructor
Knight::Knight(Knight &k) {
    board = k.board;
    colour = k.getColour();
    position = k.getPosition();
    pieceType = k.getPieceType();
    firstMove = k.isFirstMove();
    possibleNextPos = k.getPossibleNextPos();
    possibleCaptures = k.getPossibleCaptures();
}

// update possible next positions and possible next captures for Knight
void Knight::updatePossibleNextPos() {
    // clear all previous data
    possibleNextPos.clear();
    possibleCaptures.clear();

    int row = position.row;
    int col = position.col;

    // (x + 2, y + 1)
    if (row <= 6 && col <= 5) {
        possibleNextPos.emplace_back(row + 1, col + 2);
        if (board -> getBoard()[row + 1][col + 2] 
            && board -> getBoard()[row + 1][col + 2] -> getColour() != colour) {
                possibleCaptures.emplace_back(row + 1, col + 2);
        }
    }

    // (x - 2, y + 1)
    if (row <= 6 && col >= 2) {
        possibleNextPos.emplace_back(row + 1, col - 2);
        if (board -> getBoard()[row + 1][col - 2] 
            && board -> getBoard()[row + 1][col - 2] -> getColour() != colour) {
                possibleCaptures.emplace_back(row + 1, col - 2);
        }
    }

    // (x + 2, y - 1)
    if (row >= 1 && col <= 5) {
        possibleNextPos.emplace_back(row - 1, col + 2);
        if (board -> getBoard()[row - 1][col + 2] 
            && board -> getBoard()[row - 1][col + 2] -> getColour() != colour) {
                possibleCaptures.emplace_back(row - 1, col + 2);
        }
    } 

    // (x - 2, y - 1)
    if (row >= 1 && col >= 2) {
        possibleNextPos.emplace_back(row - 1, col - 2);
        if (board -> getBoard()[row - 1][col - 2] 
            && board -> getBoard()[row - 1][col - 2] -> getColour() != colour) {
                possibleCaptures.emplace_back(row - 1, col - 2);
        }
    }  

    // (x + 1, y + 2)
    if (row <= 5 && col <= 6) {
        possibleNextPos.emplace_back(row + 2, col + 1);
        if (board -> getBoard()[row + 2][col + 1] 
            && board -> getBoard()[row + 2][col + 1] -> getColour() != colour) {
                possibleCaptures.emplace_back(row + 2, col + 1);
        }
    }

    // (x - 1, y + 2)
    if (row <= 5 && col >= 1) {
        possibleNextPos.emplace_back(row + 2, col - 1);
        if (board -> getBoard()[row + 2][col - 1] 
            && board -> getBoard()[row + 2][col - 1] -> getColour() != colour) {
                possibleCaptures.emplace_back(row + 2, col - 1);
        }
    }

    // (x + 1, y - 2)
    if (row >= 2 && col <= 6) {
        possibleNextPos.emplace_back(row - 2, col + 1);
        if (board -> getBoard()[row - 2][col + 1] 
            && board -> getBoard()[row - 2][col + 1] -> getColour() != colour) {
                possibleCaptures.emplace_back(row - 2, col + 1);
        }
    }

    // (x - 1, y - 2)
    if (row >= 2 && col >= 1) {
        possibleNextPos.emplace_back(row - 2, col - 1);
        if (board -> getBoard()[row - 2][col - 1] 
            && board -> getBoard()[row - 2][col - 1] -> getColour() != colour) {
                possibleCaptures.emplace_back(row - 2, col - 1);
        }
    }
}

Knight *Knight::clone() {
    return new Knight(*this);
}

Knight::~Knight() {}

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
//     Position test_Pos{1, 1};
//     ChessBoard ch{};
//     std::shared_ptr<ChessBoard> board = std::make_shared<ChessBoard>(ch);
//     Piece *test_piece = new Knight(board, BLACK, test_Pos);
//     board -> setPiece(test_piece,test_Pos);
//     test_function(test_piece, test_Pos, board);

//     //test 2:
//     Position test_Pos_Two{0,0};
//     Piece *test_piece_Two = new Knight(board, BLACK, test_Pos_Two);
//     board -> setPiece(test_piece_Two,test_Pos_Two);
//     test_function(test_piece_Two, test_Pos_Two, board);

//     //test 3:
//     Position test_Pos_Three{2,2};
//     Piece *test_piece_Three =new Knight(board, BLACK, test_Pos_Three);
//     board -> setPiece(test_piece_Three,test_Pos_Three);
//     test_function(test_piece_Three, test_Pos_Three, board);

//     //test 4:
//     Position test_Pos_Four{0,3};
//     Piece *test_piece_Four =new Knight(board, WHITE, test_Pos_Four);
//     board -> setPiece(test_piece_Four,test_Pos_Four);
//     test_function(test_piece_Four, test_Pos_Four, board);

//     std::vector<std::vector<Piece *>> b = board.get() -> getBoard();
//     if(b[0][0]) {
//         std::cout << "here";
//     } else {
//         std::cout << b.size();
//     }
// }
