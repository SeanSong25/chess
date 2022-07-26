#include "Game.h"

#include <algorithm>
#include <iostream>

#include "ComputerLevelOne.h"
#include "ComputerLevelThree.h"
#include "ComputerLevelTwo.h"
#include "ComputerLevelFive.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"
#include "TextModifier.h"
#include "utils.h"
using namespace std;
using namespace TextColour;

Game::Game() {
    board = new ChessBoard();
    textDisplay = make_unique<TextDisplay>();
    scoreBoard = make_unique<ScoreBoard>();
    graphicDisplay = make_unique<GraphicDisplay>();
}

Game::~Game() {
    delete board;
}

void Game::play() {
    string cmd;
    cout << Modifier(FG_BLUE) << "Welcome to the chess game"
         << Modifier(FG_DEFAULT) << endl;

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

    // Read in player type (human / computer[1-4])
    string x, y;
    cin >> x >> y;

    // Initialize white and black players
    whitePlayer = initPlayer(x, WHITE);
    blackPlayer = initPlayer(y, BLACK);
    // Return if the game is not successfully initialized
    if (whitePlayer == nullptr || blackPlayer == nullptr) {
        cout << Modifier(FG_RED);
        cout << "Game failed to initialize" << endl;
        cout << "Parameter does not match human or computer[1-4]" << endl;
        cout << Modifier(FG_DEFAULT);
        return;
    }

    // Pass in the board to the players
    whitePlayer->setBoard(board);
    blackPlayer->setBoard(board);
    // Default initialize pieces if no custom setup
    if (!hasCustomSetup) {
        board->defaultInit();
    }

    // possible moves update
    board->updatePiecesPossibleMoves();

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

    announceTurn();
    notifyDisplays();
    cout << *textDisplay << endl;

    // Game is now running
    gameRunning = true;
}

void Game::announceTurn() {
    if (currentPlayer->getColour() == BLACK) {
        cout << Modifier(FG_YELLOW) << "Black player's turn"
             << Modifier(FG_DEFAULT) << endl;
    } else {
        cout << Modifier(FG_YELLOW) << "White player's turn"
             << Modifier(FG_DEFAULT) << endl;
    }
}

Player *Game::initPlayer(string player, Colour colour) {
    Player *retPtr = nullptr;

    // TODO: change the computer to computer[1-4]
    if (player == "human") {
        retPtr = new HumanPlayer(colour);
    } else if (player == "computer1") {
        retPtr = new ComputerLevelOne(colour);
    } else if (player == "computer2") {
        retPtr = new ComputerLevelTwo(colour);
    } else if (player == "computer3") {
        retPtr = new ComputerLevelThree(colour);
    } else if (player == "computer4") {
        retPtr = new ComputerLevelOne(colour);
    } else if (player == "computer5"){
        retPtr = new ComputerLevelFive(colour);
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

    endGame();
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
    bool successMove = currentPlayer->makeMove();

    // TODO: add checkmate and stalemate handles
    // check for checkmate and stalemate
    if (currentPlayer->getColour() == WHITE) {
        Piece *king = board->getBlackKing();
        int blackAvailableMoves = 0;
        bool isKingInCheck = king->isInCheck();

        // black is checkmated
        if (king->isCheckMate()) {
            std::cout << "black is checkmated" << std::endl;
        }

        // black is in check
        if (isKingInCheck) {
            std::cout << "black is in check" << std::endl;
        }

        for (auto &piece : board->getBlackPieces()) {
            for (auto &move : piece->getPossibleNextPos()) {
                if (!piece->putsKingInCheck(move)) {
                    ++blackAvailableMoves;
                }
            }
        }
        // stalemate
        if (blackAvailableMoves == 0 && !isKingInCheck) {
            std::cout << "black has no moves left, stalemate" << std::endl;
        }
    } else {
        Piece *king = board->getWhiteKing();
        int whiteAvailableMoves = 0;
        bool isKingInCheck = king->isInCheck();

        // white is checkmated
        if (king->isCheckMate()) {
            std::cout << "white is checkmated" << std::endl;
        }

        // white is in check
        if (isKingInCheck) {
            std::cout << "white is in check" << std::endl;
        }

        for (auto &piece : board->getWhitePieces()) {
            for (auto &move : piece->getPossibleNextPos()) {
                if (!piece->putsKingInCheck(move)) {
                    ++whiteAvailableMoves;
                }
            }
        }
        // stalemate
        if (whiteAvailableMoves == 0 && !king->isInCheck()) {
            std::cout << "white has no moves left, stalemate" << std::endl;
        }
    }

    if (successMove) {
        SwitchCurrentPlayer();
        announceTurn();
        notifyDisplays();
        cout << *textDisplay << endl;
    } else {
        cout << Modifier(FG_RED) << "Sorry, move not valid"
             << Modifier(FG_DEFAULT) << endl;

        announceTurn();
    }
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
            board->setupPiece();
            notifyDisplays();
            cout << *textDisplay << endl;
        }

        else if (cmd == "-") {
            board->removePiece();
            notifyDisplays();
            cout << *textDisplay << endl;
        }

        else if (cmd == "=") {
            setupColour();
        }

        else if (cmd == "done") {
            // TODO: check the kings are not in checked
            bool validity = validateChessBoard();
            if (validity == true) {
                cout << Modifier(FG_YELLOW) << "Finished board setup" << Modifier(FG_DEFAULT) << endl;
                hasCustomSetup = true;
                return;
            }
        }

        else {
            cout << Modifier(FG_RED) << "Invalid Setup command" << Modifier(FG_DEFAULT) << endl;
        }
    }
}

void Game::setupColour() {
    string colour;
    cin >> colour;

    for_each(colour.begin(), colour.end(), [](char &c) {
        c = ::tolower(c);
    });

    if (colour == "white") {
        whitePlayerStart = true;
        cout << Modifier(FG_GREEN) << "Game now start with white player" << Modifier(FG_DEFAULT) << endl;
    }

    else if (colour == "black") {
        whitePlayerStart = false;
        cout << Modifier(FG_GREEN) << "Game now start with black player" << Modifier(FG_DEFAULT) << endl;
    }

    else {
        cout << Modifier(FG_RED) << "Colour not valid"
             << Modifier(FG_DEFAULT) << endl;
    }
}

bool Game::validateChessBoard() {
    // Board contains exactly one white king and one black king
    vector<vector<Piece *>> theBoard = board->getBoard();
    bool foundBlackKing = false;
    bool foundWhiteKing = false;

    for (auto &row : theBoard) {
        for (auto &piece : row) {
            if (piece == nullptr) continue;

            // Check for white king
            if (piece->getPieceType() == KING && piece->getColour() == WHITE) {
                if (foundWhiteKing == true) {
                    cout << Modifier(FG_RED) << "Setup error: more than one white king exists. Please fix."
                         << Modifier(FG_DEFAULT) << endl;
                    return false;
                } else {
                    foundWhiteKing = true;
                }
            }

            // Check for black king
            else if (piece->getPieceType() == KING && piece->getColour() == BLACK) {
                if (foundBlackKing == true) {
                    cout << Modifier(FG_RED) << "Setup error: more than one black king exists. Please fix."
                         << Modifier(FG_DEFAULT) << endl;
                    return false;
                } else {
                    foundBlackKing = true;
                }
            }
        }
    }

    Piece *whiteKing = board->getWhiteKing();
    Piece *blackKing = board->getBlackKing();

    if (whiteKing == nullptr || blackKing == nullptr) {
        cout << Modifier(FG_RED) << "Setup error: board must contain both black king and white king. Please fix."
             << Modifier(FG_DEFAULT) << endl;
        return false;
    }

    // No pawn are on the first or last row of the board
    vector<Piece *> whitePawns = board->getWhitePawns();
    vector<Piece *> blackPawns = board->getBlackPawns();

    for (auto pawn : whitePawns) {
        int r = pawn->getPosition().row;
        if (r == 0 || r == 7) {
            cout << Modifier(FG_RED) << "Setup error: no pawn should exists on the first or last row of the board. Please fix."
                 << Modifier(FG_DEFAULT) << endl;
            return false;
        }
    }

    for (auto pawn : blackPawns) {
        int r = pawn->getPosition().row;
        if (r == 0 || r == 7) {
            cout << Modifier(FG_RED) << "Setup error: no pawn should exists on the first or last row of the board. Please fix."
                 << Modifier(FG_DEFAULT) << endl;
            return false;
        }
    }

    // Neither king should be in check
    board->updatePiecesPossibleMoves();

    if (whiteKing->isInCheck()) {
        cout << Modifier(FG_RED) << "Setup error: white king is in check. Please fix."
             << Modifier(FG_DEFAULT) << endl;
        return false;
    }

    if (blackKing->isInCheck()) {
        cout << Modifier(FG_RED) << "Setup error: black king is in check. Please fix."
             << Modifier(FG_DEFAULT) << endl;
        return false;
    }

    return true;
}

void Game::notifyDisplays() {
    textDisplay->notifyTextDisplay(board->getBoard());
    graphicDisplay->notifyGraphicDisplay(board->getBoard());
}

void Game::endGame() {
    gameRunning = false;
    hasCustomSetup = false;
    whitePlayerStart = true;
    if (whitePlayer) delete whitePlayer;
    if (blackPlayer) delete blackPlayer;
    board->destroy();
}