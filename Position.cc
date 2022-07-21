#include "utils.h"
Position::Position(std::string s){
    char c = s[0];
    col = (int)c - (int)'a';
    c = s[1];
    row = (int) c;
}

Position::Position(){
    row = -1;
    col = -1;
}

int Position::getRowIndex(){
    return 8 - row;
}

int Position::getColumnIndex(){
    return col;
}