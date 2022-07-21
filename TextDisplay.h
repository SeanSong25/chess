#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H
#include <iostream>
#include <vector>

#include "Piece.h"

class TextDisplay {
    std::vector<std::vector<char>> textBoard;

  public:
    TextDisplay();
    friend std::ostream& operator<<(std::ostream&, const TextDisplay&);
    void notify(Piece&);
};

#endif