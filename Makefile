CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g
EXEC = biquadris
OBJECTS = main.o biquadris.o player.o board.o level.o block.o level_0.o level_1.o level_2.o level_3.o level_4.o iblock.o jblock.o sblock.o tblock.o starblock.o zblock.o lblock.o oblock.o cell.o coordinate.o textdisplay.o window.o graphics.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
