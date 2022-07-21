#include "Game.h"

#include <algorithm>
#include <iostream>

#include "ComputerPlayer.h"
#include "HumanPlayer.h"
#include "TextModifier.h"
#include "utils.h"
using namespace std;
using namespace TextColour;

Game::Game() {
    scoreBoard = make_unique<ScoreBoard>();
    board = make_shared<ChessBoard>();
    textDisplay = make_unique<TextDisplay>();
    graphicDisplay = make_unique<GraphicDisplay>();
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
        } else if (cmd == "undo") {
        }
    }

    // Print final score
    cout << Modifier(FG_MAGENTA) << "Final Score:"
         << Modifier(FG_DEFAULT) << endl;
    scoreBoard->printScore();
}

/* Start a new game with white-player and black-player
   parameter can be human or computer[1-4] */
void Game::startGame() {
    if (gameRunning == true) {
        cout << Modifier(FG_RED);
        cout << "Game already started" << endl;
        cout << Modifier(FG_DEFAULT);
        return;
    }

    string x, y;
    cin >> x >> y;

    // Initialize white and black players
    whitePlayer = initPlayer(x);
    blackPlayer = initPlayer(y);

    // Return if the game is not successfully initialized
    if (whitePlayer == nullptr || blackPlayer == nullptr) {
        cout << Modifier(FG_RED);
        cout << "Game failed to initialize" << endl;
        cout << "Parameter does not match human or computer[1-4]" << endl;
        cout << Modifier(FG_DEFAULT);
        return;
    }

    // TODO: Initialize pieces in the board
    if (hasCustomSetup) {
    }

    // Successfully initialized the game
    cout << Modifier(FG_GREEN);
    cout << "Game initialized" << endl;
    cout << "White player: " << x << endl;
    cout << "Black player: " << y << endl;
    cout << Modifier(FG_DEFAULT);

    // Set current player
    if (whitePlayerStart) {
        currentPlayer = whitePlayer;
    } else {
        currentPlayer = blackPlayer;
    }

    // announceTurn();

    // if (whitePlayerStart == false) {
    //     cout << Modifier(FG_YELLOW) << "Black player's turn"
    //          << Modifier(FG_DEFAULT) << endl;
    // } else {
    //     cout << Modifier(FG_YELLOW) << "White player's turn"
    //          << Modifier(FG_DEFAULT) << endl;
    // }

    // Game is now running
    gameRunning = true;
}

void Game::announceTurn() {
    if (currentPlayer->colour == BLACK) {
        cout << Modifier(FG_YELLOW) << "Black player's turn"
             << Modifier(FG_DEFAULT) << endl;
    } else {
        cout << Modifier(FG_YELLOW) << "White player's turn"
             << Modifier(FG_DEFAULT) << endl;
    }
}

// TODO: Helper function for initializing human and computer players
// TODO: Pass in the shared pointer board to the players
Player* Game::initPlayer(string player) {
    Player* retPtr = nullptr;

    // TODO: change the computer to computer[1-4]
    if (player == "human") {
        retPtr = new HumanPlayer();
    } else if (player == "computer1") {
        retPtr = new ComputerPlayer();
    } else if (player == "computer2") {
        retPtr = new ComputerPlayer();
    } else if (player == "computer3") {
        retPtr = new ComputerPlayer();
    } else if (player == "computer4") {
        retPtr = new ComputerPlayer();
    }

    return retPtr;
}

void Game::resignGame() {
    if (gameRunning == false) {
        cout << Modifier(FG_RED) << "Ay game not started yet -_-"
             << Modifier(FG_DEFAULT) << endl;
        return;
    }

    if (currentPlayer->playerType() != PlayerType::HUMAN) {
        cout << Modifier(FG_RED) << "Computer cannot resign game"
             << Modifier(FG_DEFAULT) << endl;
        return;
    }

    if (currentPlayer == blackPlayer) {
        cout << Modifier(FG_YELLOW);
        cout << "Black player resigned" << endl;
        cout << "White player win the game!" << endl;
        cout << Modifier(FG_DEFAULT);

        scoreBoard->updateScore(WHITE);
    } else {
        cout << Modifier(FG_YELLOW);
        cout << "White player resigned" << endl;
        cout << "Black player wins the game!" << endl;
        cout << Modifier(FG_DEFAULT);

        scoreBoard->updateScore(BLACK);
    }

    cout << Modifier(FG_MAGENTA) << "Print current scoreboard:"
         << Modifier(FG_DEFAULT) << endl;
    scoreBoard->printScore();

    gameRunning = false;
}

void Game::SwitchCurrentPlayer() {
    if (currentPlayer == blackPlayer) {
        currentPlayer = whitePlayer;
    } else {
        currentPlayer = blackPlayer;
    }
}

void Game::moveGame() {
    if (gameRunning == false) {
        cout << Modifier(FG_RED) << "Ay game not started yet -_-"
             << Modifier(FG_DEFAULT) << endl;
        return;
    }

    // TODO: need to check whether the move is successful
    currentPlayer->makeMove();

    SwitchCurrentPlayer();
    // anounceTurn();

    // cout << Modifier(FG_YELLOW);
    // if (currentPlayer == blackPlayer) {
    //     cout << "Black player's turn" << endl;
    // } else {
    //     cout << "White player's turn" << endl;
    // }
    // cout << Modifier(FG_YELLOW);

    // Print board
    cout << *textDisplay << endl;
}

void Game::setupGame() {
    if (gameRunning == true) {
        cout << Modifier(FG_RED) << "Please setup before game start"
             << Modifier(FG_DEFAULT) << endl;
        return;
    }

    cout << Modifier(FG_YELLOW) << "Enters the setup mode" << Modifier(FG_DEFAULT) << endl;

    string cmd;
    while (cin >> cmd) {
        if (cmd == "+") {
            // TODO: add piece to board

            char piece;
            string pos;
            cin >> piece >> pos;

            cout << Modifier(FG_GREEN) << "Places the piece " << piece << " on the square " << pos << Modifier(FG_DEFAULT) << endl;
        }

        else if (cmd == "-") {
            // TODO: delete piece from board
            string pos;
            cin >> pos;

            cout << Modifier(FG_GREEN) << "Removes the piece from square " << pos << Modifier(FG_DEFAULT) << endl;
        }

        else if (cmd == "=") {
            string colour;
            cin >> colour;

            // Convert colour to lowercase
            std::for_each(colour.begin(), colour.end(), [](char& c) {
                c = ::tolower(c);
            });

            if (colour == "white") {
                whitePlayerStart = true;
                cout << Modifier(FG_GREEN) << "Game now start with white player" << Modifier(FG_DEFAULT) << endl;
            } else if (colour == "black") {
                whitePlayerStart = false;
                cout << Modifier(FG_GREEN) << "Game now start with black player" << Modifier(FG_DEFAULT) << endl;
            } else {
                cout << Modifier(FG_RED) << "Colour not valid" << Modifier(FG_DEFAULT) << endl;
            }

        } else if (cmd == "done") {
            cout << Modifier(FG_YELLOW) << "Finished board setup" << Modifier(FG_DEFAULT) << endl;
            return;
        }

        else {
            cout << Modifier(FG_RED) << "Invalid Setup command" << Modifier(FG_DEFAULT) << endl;
        }
    }

    hasCustomSetup = true;
}