#include "GraphicDisplay.h"
using namespace std;
using namespace SDL;
#include <iostream>

SDL_Runner r;

GraphicDisplay::GraphicDisplay() {
    square_height = (screen_height - padding * 2) / 8;
    square_width = (screen_width - padding * 2) / 8;
    s = new Screen{screen_height, screen_width, "Chess Game"};

    s->add_img("dark_square", "img/dark_square.png");
    s->add_img("light_square", "img/light_square.png");

    s->add_img("b_bishop", "img/b_bishop.png");
    s->add_img("b_king", "img/b_king.png");
    s->add_img("b_knight", "img/b_knight.png");
    s->add_img("b_pawn", "img/b_pawn.png");
    s->add_img("b_queen", "img/b_queen.png");
    s->add_img("b_rook", "img/b_rook.png");

    s->add_img("w_bishop", "img/w_bishop.png");
    s->add_img("w_king", "img/w_king.png");
    s->add_img("w_knight", "img/w_knight.png");
    s->add_img("w_pawn", "img/w_pawn.png");
    s->add_img("w_queen", "img/w_queen.png");
    s->add_img("w_rook", "img/w_rook.png");

    drawBoard();

    s->update();
}

void GraphicDisplay::drawBoard() {
    // Draw the background
    SDL::Colour brown{'\x31', '\x11', '\x08'};
    s->draw_rect(0, 0, screen_width, screen_height, brown);

    // Draw square tiles
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if ((r + c) % 2 == 0) {
                s->draw_square("light_square", c * square_width + padding, r * square_height + padding, square_width, square_height);
            } else {
                s->draw_square("dark_square", c * square_width + padding, r * square_height + padding, square_width, square_height);
            }
        }
    }

    // Draw the coordinates
    SDL::Colour light_brown{'\xa9', '\x8e', '\x87'};
    int l_offset = 12;
    int t_offset = padding + square_height / 2 - 15;
    s->draw_string("8", l_offset, 0 * square_height + t_offset, light_brown);
    s->draw_string("7", l_offset, 1 * square_height + t_offset, light_brown);
    s->draw_string("6", l_offset, 2 * square_height + t_offset, light_brown);
    s->draw_string("5", l_offset, 3 * square_height + t_offset, light_brown);
    s->draw_string("4", l_offset, 4 * square_height + t_offset, light_brown);
    s->draw_string("3", l_offset, 5 * square_height + t_offset, light_brown);
    s->draw_string("2", l_offset, 6 * square_height + t_offset, light_brown);
    s->draw_string("1", l_offset, 7 * square_height + t_offset, light_brown);

    int x_offset = padding + square_width / 2 - 10;
    int y_offset = padding + 8 * square_height + 5;
    s->draw_string("a", 0 * square_width + x_offset, y_offset, light_brown);
    s->draw_string("b", 1 * square_width + x_offset, y_offset, light_brown);
    s->draw_string("c", 2 * square_width + x_offset, y_offset, light_brown);
    s->draw_string("d", 3 * square_width + x_offset, y_offset, light_brown);
    s->draw_string("e", 4 * square_width + x_offset, y_offset, light_brown);
    s->draw_string("f", 5 * square_width + x_offset, y_offset, light_brown);
    s->draw_string("g", 6 * square_width + x_offset, y_offset, light_brown);
    s->draw_string("h", 7 * square_width + x_offset, y_offset, light_brown);
}

GraphicDisplay::~GraphicDisplay() {
    delete s;
}

void GraphicDisplay::notifyGraphicDisplay(const vector<vector<Piece*>>& theBoard) {
    drawBoard();

    // Draw Pieces
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (theBoard[r][c] != nullptr) {
                drawPiece(theBoard[r][c]);
            }
        }
    }

    s->update();
}

void GraphicDisplay::drawPiece(Piece* piece) {
    PieceType pieceType = piece->getPieceType();
    Position pos = piece->getPosition();
    int x = pos.col * square_width + padding;
    int y = pos.row * square_height + padding;

    if (pieceType == ROOK && piece->getColour() == WHITE) {
        s->draw_piece("w_rook", x, y, square_width, square_height);
    } else if (pieceType == KNIGHT && piece->getColour() == WHITE) {
        s->draw_piece("w_knight", x, y, square_width, square_height);
    } else if (pieceType == BISHOP && piece->getColour() == WHITE) {
        s->draw_piece("w_bishop", x, y, square_width, square_height);
    } else if (pieceType == QUEEN && piece->getColour() == WHITE) {
        s->draw_piece("w_queen", x, y, square_width, square_height);
    } else if (pieceType == KING && piece->getColour() == WHITE) {
        s->draw_piece("w_king", x, y, square_width, square_height);
    } else if (pieceType == PAWN && piece->getColour() == WHITE) {
        s->draw_piece("w_pawn", x, y, square_width, square_height);
    }

    else if (pieceType == ROOK && piece->getColour() == BLACK) {
        s->draw_piece("b_rook", x, y, square_width, square_height);
    } else if (pieceType == KNIGHT && piece->getColour() == BLACK) {
        s->draw_piece("b_knight", x, y, square_width, square_height);
    } else if (pieceType == BISHOP && piece->getColour() == BLACK) {
        s->draw_piece("b_bishop", x, y, square_width, square_height);
    } else if (pieceType == QUEEN && piece->getColour() == BLACK) {
        s->draw_piece("b_queen", x, y, square_width, square_height);
    } else if (pieceType == KING && piece->getColour() == BLACK) {
        s->draw_piece("b_king", x, y, square_width, square_height);
    } else if (pieceType == PAWN && piece->getColour() == BLACK) {
        s->draw_piece("b_pawn", x, y, square_width, square_height);
    }
}