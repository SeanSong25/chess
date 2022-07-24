#include "GraphicDisplay.h"
using namespace std;
using namespace SDL;
#include <iostream>

SDL_Runner r;

GraphicDisplay::GraphicDisplay() {
    // Screen s{800, 800, "Chess Game"};
    s = new Screen{800, 800, "Chess Game"};

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

    // Draw square tiles
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if ((r + c) % 2 == 0) {
                s->draw_img("light_square", c * square_width, r * square_height);
            } else {
                s->draw_img("dark_square", c * square_width, r * square_height);
            }
        }
    }

    s->update();
}

GraphicDisplay::~GraphicDisplay() {
    delete s;
}

void GraphicDisplay::notifyGraphicDiplay(const vector<vector<Piece*>>& theBoard) {}