#ifndef GRAPHIC_DISPLAY_H
#define GRAPHIC_DISPLAY_H
#include "Piece.h"
#include "sdl_wrap.h"

class GraphicDisplay {
    SDL::Screen* s;
    int screen_height = 758;
    int screen_width = 758;
    int padding = 40;
    int square_width;
    int square_height;
    void drawPiece(Piece*);
    void drawBoard();

  public:
    GraphicDisplay();
    ~GraphicDisplay();
    void notifyGraphicDisplay(const std::vector<std::vector<Piece*>>& theBoard);
};

#endif
