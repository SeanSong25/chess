#include "Player.h"
using namespace std;
void Player::setBoard(shared_ptr<ChessBoard> board){
    this->board = board;
}

Player::~Player(){}