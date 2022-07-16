CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = myprogram
OBJECTS = main.o
DEPENDS = ${OBJECTS:.o=.d}

$EXEC: ${OBJECTS}
	${CXX} ${CXXFLAFS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
		rm ${OBJECTS} ${EXEC} ${DEPENDS}