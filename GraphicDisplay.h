#ifndef GRAPHIC_DISPLAY_H
#define GRAPHIC_DISPLAY_H
#include "Piece.h"
#include "sdl_wrap.h"

class GraphicDisplay {
    SDL::Screen* s;
    int square_width = 100;
    int square_height = 100;

  public:
    GraphicDisplay();
    ~GraphicDisplay();
    void notifyGraphicDiplay(const std::vector<std::vector<Piece*>>& theBoard);
};

#endif
