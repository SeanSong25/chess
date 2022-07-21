#include "King.h"

// constructor
King::King(std::shared_ptr<ChessBoard> board, Colour colour, Position position): 
    Piece{board, colour, position, PieceType::KING}, 
    firstMove{true},
    attackingPieces{std::vector<Piece *> ()} {}

// get possible next positions and possible next captures for King
void King::updatePossibleNextPos() {
    // clear all previous data
    possibleNextPos.clear();
    possibleCaptures.clear();

    // regular move
    int row = position.row;
    int col = position.col;

    // top
    if (row >= 1) {
        possibleNextPos.emplace_back(row - 1, col);
        if (board -> getBoard()[row - 1][col] 
            && board -> getBoard()[row - 1][col] -> getColour() != colour) {
                possibleCaptures.emplace_back(row - 1, col);
        }
    }

    // bottom
    if (row <= 6) {
        possibleNextPos.emplace_back(row + 1, col);
        if (board -> getBoard()[row + 1][col] 
            && board -> getBoard()[row + 1][col] -> getColour() != colour) {
                possibleCaptures.emplace_back(row + 1, col);
        }
    }

    // left
    if (col >= 1) {
        possibleNextPos.emplace_back(row, col - 1);
        if (board -> getBoard()[row][col - 1] 
            && board -> getBoard()[row][col - 1] -> getColour() != colour) {
                possibleCaptures.emplace_back(row, col - 1);
        }
    }

    // right
    if (col <= 6) {
        possibleNextPos.emplace_back(row, col + 1);
        if (board -> getBoard()[row][col + 1] 
            && board -> getBoard()[row][col + 1] -> getColour() != colour) {
                possibleCaptures.emplace_back(row, col + 1);
        }
    }

    // top right
    if (row >= 1 && col <= 6) {
        possibleNextPos.emplace_back(row - 1, col + 1);
        if (board -> getBoard()[row - 1][col + 1] 
            && board -> getBoard()[row - 1][col + 1] -> getColour() != colour) {
                possibleCaptures.emplace_back(row - 1, col + 1);
        }
    }

    // bottom right
    if (row <= 6 && col <= 6) {
        possibleNextPos.emplace_back(row + 1, col + 1);
        if (board -> getBoard()[row + 1][col + 1] 
            && board -> getBoard()[row + 1][col + 1] -> getColour() != colour) {
                possibleCaptures.emplace_back(row + 1, col + 1);
        }
    }

    // top left
    if (row >= 1 && col >= 1) {
        possibleNextPos.emplace_back(row - 1, col - 1);
        if (board -> getBoard()[row - 1][col - 1] 
            && board -> getBoard()[row - 1][col - 1] -> getColour() != colour) {
                possibleCaptures.emplace_back(row - 1, col - 1);
        }
    }

    // bottom left
    if (row <= 6 && col >= 1) {
        possibleNextPos.emplace_back(row + 1, col - 1);
        if (board -> getBoard()[row + 1][col - 1] 
            && board -> getBoard()[row + 1][col - 1] -> getColour() != colour) {
                possibleCaptures.emplace_back(row + 1, col - 1);
        }
    }

    // castling
    std::vector<Piece *> rooks;
    if (colour == Colour::BLACK) {
        rooks = board -> getBlackRooks();
    } else {
        rooks = board -> getWhiteRooks();
    }

    if (canCastle(rooks[0])) {
        possibleNextPos.emplace_back(row, col - 2);
    }

    if (canCastle(rooks[1])) {
        possibleNextPos.emplace_back(row, col + 2);
    }
}

// return true if player can castle
bool King::canCastle(Piece *rook) {
    if (!firstMove || !rook -> isFirstMove()) {
        return false;
    }

    Position rookPos = rook -> getPosition();
    if (position.col < rookPos.col) {
        if (board -> getBoard()[position.row][position.col + 1] || 
            board -> getBoard()[position.row][position.col + 2]) {
                return false;
        }
        Position middlePos = Position(position.row, position.col + 1);
        Position finalPos = Position(position.row, position.col + 2);
        if (canBeCaptured(position) || canBeCaptured(middlePos) || canBeCaptured(finalPos)) {
            return false;
        }
    } else {
        if (board -> getBoard()[position.row][position.col - 1] || 
            board -> getBoard()[position.row][position.col - 2]) {
                return false;
        }
        Position middlePos = Position(position.row, position.col - 1);
        Position finalPos = Position(position.row, position.col - 2);
        if (canBeCaptured(position) || canBeCaptured(middlePos) || canBeCaptured(finalPos)) {
            return false;
        }
    }
}

// get attacking pieces 
void King::getAttackingPieces() {
    // clear any previous attacking pieces
    attackingPieces.clear();

    std::vector<Piece *> opponentPieces;
    if (colour == Colour::WHITE) {
        opponentPieces = board -> getBlackPieces();
    } else {
        opponentPieces = board -> getWhitePieces();
    }

    for (auto &piece : opponentPieces) {
        std::vector<Position> captures = piece -> getPossibleCaptures();
        for (auto &capture: captures) {
            if (capture == position) {
                attackingPieces.emplace_back(piece);
                break;
            }
        }
    }
}

// called after each opponent move (possible next moves should be updated)
bool King::isCheckMate() {
    // check if it is in check
    if (!canBeCaptured(position)) {
        return false;
    }

    // if it is in check, get attacking pieces
    getAttackingPieces();

    // check if king can move to escape
    if (possibleNextPos.size() == 0) {
        return true;
    }

    for (auto &pos : possibleNextPos) {
        if (!canBeCaptured(pos)) {
            return false;
        }
    }

    // check if there is more than one attacking piece
    // it is impossible to escape when there is more than one attacking piece
    if (attackingPieces.size() > 1) {
        return true;
    }

    // check if the attacking piece can be captured
    if (canBeCaptured(attackingPieces[0] -> getPosition())) {
        return false;
    }

    // check if the attacking piece is a knight
    // (knight can jump over any block)
    if (attackingPieces[0] -> getPieceType() == PieceType::KNIGHT) {
        return true;
    }

    // check if a piece can be moved between the attacking piece and king to avoid the attack
    std::vector<Piece *> playerPieces;
    if (colour == Colour::BLACK) {
        playerPieces = board -> getWhitePieces();
    } else {
        playerPieces = board -> getBlackPieces();
    }
    for (auto &piece : playerPieces) {
        for (auto &pos : piece -> getPossibleNextPos()) {
            
        }
    }

    return true;
}

King::~King() {}