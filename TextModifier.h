/* -------------------------------------------------------------
This file is used to change the colour of text output to the command
usage: cout << TextColour::Modifier(Code) << [text] << endl;
--------------------------------------------------------------- */

#ifndef TEXT_MODIFIER_H
#define TEXT_MODIFIER_H
#include <iostream>

namespace TextColour {
enum Code {
    FG_BLACK = 30,
    FG_RED = 31,    // print warning
    FG_GREEN = 32,  // print success
    FG_YELLOW = 33,
    FG_BLUE = 34,
    FG_MAGENTA = 35,  // print score
    FG_CYAN = 36,
    FG_WHITE = 37,
    FG_DEFAULT = 39,
    BG_RED = 41,
    BG_GREEN = 42,
    BG_BLUE = 44,
    BG_DEFAULT = 49
};

class Modifier {
    Code code;

  public:
    Modifier(Code);

    friend std::ostream&
    operator<<(std::ostream& os, const Modifier& mod) {
        return os << "\033[" << mod.code << "m";
    }
};
}  // namespace TextColour

#endif
