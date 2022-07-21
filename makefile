CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = chessProgram
OBJECTS = main.o Piece.o ChessBoard.o Game.o ComputerPlayer.o HumanPlayer.o Observer.o Pawn.o Rook.o Knight.o King.o Queen.o Bishop.o utils.o
DEPENDS = ${OBJECTS:.o=.d}

$EXEC: ${OBJECTS}
	${CXX} ${CXXFLAFS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
		rm ${OBJECTS} ${EXEC} ${DEPENDS}