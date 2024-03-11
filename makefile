
#g++ $@.cpp -lSDL2 -lSDL2_image -o $@
# Rule to compile any .cpp file into an executable with the same name

CXX = g++
TARGET = main
LFLAGS = -lSDL2 -lSDL2_image

${TARGET}: ${TARGET}.cpp
	${CXX} ${TARGET}.cpp ${LFLAGS} -o ${TARGET}

clean:
	rm -f ${TARGET}