#CC specifies which compiler we're using
CC = gcc

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main

#This is the target that compiles our executable
all : functions.o main.o trace.o
	$(CC) main.o functions.o trace.o $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)


functions.o: functions.c
	$(CC) -c functions.c $(COMPILER_FLAGS) $(LINKER_FLAGS)


trace.o: trace.c
	$(CC) -c trace.c $(COMPILER_FLAGS) $(LINKER_FLAGS)


main.o: main.c functions.h trace.h
	$(CC) -c main.c $(COMPILER_FLAGS) $(LINKER_FLAGS)

clear:
	rm *.o main
