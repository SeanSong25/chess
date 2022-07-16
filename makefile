CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = myprogram
OBJECTS = main.o Piece.o ChessBoard.o Game.o Player.o ComputerPlayer.o HumanPlayer.o Observer.o Pawn.o Rook.o Knight.o King.o Queen.o
DEPENDS = ${OBJECTS:.o=.d}

$EXEC: ${OBJECTS}
	${CXX} ${CXXFLAFS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
		rm ${OBJECTS} ${EXEC} ${DEPENDS}