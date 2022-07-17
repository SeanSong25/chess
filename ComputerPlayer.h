#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

class ComputerPlayer : public Player {
  public:
    ComputerPlayer();
    virtual ~ComputerPlayer();
    void makeMove() override;
};

#endif