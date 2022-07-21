#ifndef GAME_H
#define GAME_H
#include <memory>

#include "ChessBoard.h"
#include "GraphicDisplay.h"
#include "Player.h"
#include "ScoreBoard.h"
#include "TextDisplay.h"

class Game {
    std::shared_ptr<ChessBoard> board;
    Player* whitePlayer;
    Player* blackPlayer;
    Player* currentPlayer;
    std::unique_ptr<TextDisplay> textDisplay;
    std::unique_ptr<ScoreBoard> scoreBoard;
    std::unique_ptr<GraphicDisplay> graphicDisplay;

    // Helper functions
    bool gameRunning = false;
    bool hasCustomSetup = false;
    bool whitePlayerStart = true;
    void SwitchCurrentPlayer();
    Player* initPlayer(std::string);
    void startGame();
    void setupGame();
    void resignGame();
    void moveGame();
    void announceTurn();

  public:
    Game();
    ~Game() = default;
    void play();
};

#endif