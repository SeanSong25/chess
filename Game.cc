#include "Game.h"

#include <algorithm>
#include <iostream>

#include "ComputerLevelFour.h"
#include "ComputerLevelOne.h"
#include "ComputerLevelThree.h"
#include "ComputerLevelTwo.h"
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
    if (whitePlayer) delete whitePlayer;
    if (blackPlayer) delete blackPlayer;
}

void Game::play() {
    string cmd;
    cout << Modifier(FG_BLUE) << "Welcome to the chess game"
         << Modifier(FG_DEFAULT) << endl;

    while (cin >> cmd && cmd != "quit") {
        if (cmd == "game") {
            this->startGame();
        } else if (cmd == "resign") {
            this->resignGame();
        } else if (cmd == "move") {
            this->moveGame();
        } else if (cmd == "setup") {
            this->setupGame();
        } else if (cmd == "undo") {
        } else {
            cout << "Command not found." << endl;
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
        retPtr = new ComputerLevelFour(colour);
    } else if (player == "computer5") {
        retPtr = new ComputerLevelOne(colour);
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

    bool successMove = currentPlayer->makeMove();

    // Check check/checkmate/stalemate after white player move
    if (currentPlayer->getColour() == WHITE) {
        Piece *king = board->getBlackKing();
        int blackAvailableMoves = 0;
        bool isKingInCheck = king->isInCheck();

        // black is checkmated
        if (king->isCheckMate()) {
            std::cout << Modifier(FG_CYAN) << "Checkmate! White wins!" << Modifier(FG_DEFAULT) << std::endl;

            // Game ended after checkmate
            scoreBoard->updateScore(WHITE);
            endGame();
            return;
        }

        // black is in check
        if (isKingInCheck) {
            std::cout << Modifier(FG_YELLOW) << "Black is in check." << Modifier(FG_DEFAULT) << std::endl;
        }

        // Stalemate
        for (auto &piece : board->getBlackPieces()) {
            for (auto &move : piece->getPossibleNextPos()) {
                if (!piece->putsKingInCheck(move)) {
                    ++blackAvailableMoves;
                }
            }
        }
        if (blackAvailableMoves == 0 && !isKingInCheck) {
            std::cout << Modifier(FG_CYAN) << "Stalemate!" << Modifier(FG_DEFAULT) << std::endl;
            scoreBoard->updateTie();
            endGame();
            return;
        }
    }

    // Check check/checkmate/stalemate after black player move
    else {
        Piece *king = board->getWhiteKing();
        int whiteAvailableMoves = 0;
        bool isKingInCheck = king->isInCheck();

        // white is checkmated
        if (king->isCheckMate()) {
            std::cout << Modifier(FG_CYAN) << "Checkmate! Black wins!" << Modifier(FG_DEFAULT) << std::endl;
            scoreBoard->updateScore(BLACK);
            endGame();
            return;
        }

        // white is in check
        if (isKingInCheck) {
            std::cout << Modifier(FG_YELLOW) << "White is in check." << Modifier(FG_DEFAULT) << std::endl;
        }

        // stalemate
        for (auto &piece : board->getWhitePieces()) {
            for (auto &move : piece->getPossibleNextPos()) {
                if (!piece->putsKingInCheck(move)) {
                    ++whiteAvailableMoves;
                }
            }
        }
        if (whiteAvailableMoves == 0 && !king->isInCheck()) {
            std::cout << Modifier(FG_CYAN) << "Stalemate!" << Modifier(FG_DEFAULT) << std::endl;
            scoreBoard->updateTie();
            endGame();
            return;
        }
    }

    // Check if the move is valid
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
            // User can only exit setup mode if the chessboard is at valid state
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

    // Board cannot be stalemate
    int availableMoves = 0;
    if (whitePlayerStart == true) {
        for (auto &piece : board->getWhitePieces()) {
            for (auto &move : piece->getPossibleNextPos()) {
                if (!piece->putsKingInCheck(move)) {
                    ++availableMoves;
                }
            }
        }
    } else {
        for (auto &piece : board->getBlackPieces()) {
            for (auto &move : piece->getPossibleNextPos()) {
                if (!piece->putsKingInCheck(move)) {
                    ++availableMoves;
                }
            }
        }
    }
    if (availableMoves == 0) {
        cout << Modifier(FG_RED) << "Setup error: this is a stalemate setup. Please fix."
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
    cout << Modifier(FG_BLUE) << "Current game ended" << Modifier(FG_DEFAULT) << endl;
    cout << Modifier(FG_MAGENTA) << "Print current scoreboard:" << Modifier(FG_DEFAULT) << endl;
    scoreBoard->printScore();
    gameRunning = false;
    hasCustomSetup = false;
    whitePlayerStart = true;
    if (whitePlayer) delete whitePlayer;
    if (blackPlayer) delete blackPlayer;
    cout << "Enter anything to start next game" << endl;
    string foo;
    cin >> foo;
    board->destroy();
    notifyDisplays();
    cout << Modifier(FG_BLUE) << "Board cleared" << Modifier(FG_DEFAULT) << endl;
}