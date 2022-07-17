#include "Game.h"

#include <iostream>

#include "ComputerPlayer.h"
#include "HumanPlayer.h"
#include "TextModifier.h"
using namespace std;
using namespace TextColour;

Game::Game() {
    scoreBoard = make_unique<ScoreBoard>();
    board = make_shared<ChessBoard>();
    textDisplay = make_unique<TextDisplay>();
    graphicDisplay = make_unique<GraphicDisplay>();
    gameRunning = false;
}

void Game::play() {
    string cmd;

    while (cin >> cmd) {
        if (cmd == "game") {
            this->startGame();
        } else if (cmd == "resign") {
            this->resignGame();
        } else if (cmd == "move") {
            this->moveGame();
        } else if (cmd == "setup") {
            this->setupGame();
        }
    }

    // Print final score
    cout << Modifier(FG_MAGENTA) << "Final Score:"
         << Modifier(FG_DEFAULT) << endl;
    scoreBoard->printScore();
}

void Game::startGame() {
    /* Start a new game with white-player and black-player
       parameter can be human or computer[1-4] */

    string x, y;
    cin >> x >> y;

    // TODO: Initialize white and black players
    whitePlayer = initPlayer(x);
    blackPlayer = initPlayer(y);
    currentPlayer = whitePlayer;

    // Return if the game is not successfully initialized
    if (whitePlayer == nullptr || blackPlayer == nullptr) {
        cout << Modifier(FG_RED);
        cout << "Game failed to initialize" << endl;
        cout << "Parameter does not match human or computer[1-4]" << endl;
        cout << Modifier(FG_DEFAULT);
        return;
    }

    // TODO: Pass in the shared pointer board to the players

    // Successfully initialized the game
    cout << Modifier(FG_GREEN);
    cout << "Game initialized" << endl;
    cout << "White player: " << x << endl;
    cout << "Black player: " << y << endl;
    cout << Modifier(FG_DEFAULT);

    // Game is now running
    gameRunning = true;
}

// TODO: Helper function for initializing human and computer players
Player* Game::initPlayer(string player) {
    Player* retPtr = nullptr;

    if (player == "human") {
    } else if (player == "computer1") {
    } else if (player == "computer2") {
    } else if (player == "computer3") {
    } else if (player == "computer4") {
    }

    return retPtr;
}

void Game::resignGame() {
    // TODO: check if the current player is human

    cout << Modifier(FG_YELLOW) << "Player resigned"
         << Modifier(FG_DEFAULT) << endl;

    // TODO: update scoreboard
}

void Game::moveGame() {}
void Game::setupGame() {}