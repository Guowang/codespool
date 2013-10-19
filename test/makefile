CC = g++
FLAGS = -ggdb
OBJ = map.o planner.o


all: main
main: program.cpp ${OBJ}
	${CC} ${FLAGS} -o main -lncurses ${OBJ} program.cpp
planner.o: DPlanner.cpp DPlanner.h
	${CC} ${FLAGS} -c -o planner.o DPlanner.cpp

clean: 
	rm main
