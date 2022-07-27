#include "Player.h"
using namespace std;

void Player::setBoard(ChessBoard* board){
    this->board = board;
}

Colour Player::getColour() {
    return colour;
}

Player:: ~Player(){
    board = nullptr;
}
