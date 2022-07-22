CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = chessProgram
OBJECTS = Player.o utils.o ChessBoard.o Piece.o Knight.o HumanPlayer.o
DEPENDS = ${OBJECTS:.o=.d}

$EXEC: ${OBJECTS}
	${CXX} ${CXXFLAFS} ${OBJECTS} -o ${EXEC} 

-include ${DEPENDS}

.PHONY: clean

clean:
		rm ${OBJECTS} ${EXEC} ${DEPENDS}