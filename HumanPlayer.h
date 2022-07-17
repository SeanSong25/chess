#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

class HumanPlayer : public Player {
  public:
    HumanPlayer();
    ~HumanPlayer();
    void makeMove() override;
};

#endif