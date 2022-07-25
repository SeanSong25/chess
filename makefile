CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = chessProgram
OBJECTS = main.o Piece.o ChessBoard.o Game.o Player.o ComputerPlayer.o ComputerLevelOne.o ComputerLevelTwo.o ComputerLevelThree.o HumanPlayer.o Observer.o Pawn.o Rook.o Knight.o King.o Queen.o Bishop.o utils.o ScoreBoard.o TextDisplay.o GraphicDisplay.o TextModifier.o sdl_wrap.o
DEPENDS = ${OBJECTS:.o=.d}

$EXEC: ${OBJECTS}
	${CXX} ${CXXFLAFS} ${OBJECTS} -o ${EXEC} -lSDL2 -lSDL2_image -lSDL2_ttf

-include ${DEPENDS}

.PHONY: clean

clean:
		rm ${OBJECTS} ${EXEC} ${DEPENDS}