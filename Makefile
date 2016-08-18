CXX = g++
CXXFLAGS = -Wall -MMD -g
EXEC = flood
OBJECTS = main.o textdisplay.o game.o view.o controller.o cell.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
