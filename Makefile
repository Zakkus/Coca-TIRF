CC=g++
CFLAGS=-std=c++11 -O3
LIBS=-lSDL2 -lSDL2_image
SRC=Main.cc SDL_init.cc Filters.cc Utils.cc
OBJ=$(SRC:.cc=.o)
EXE=coca

all:
	$(CC) $(CFLAGS) $(LIBS) -o $(EXE) $(SRC)

clean:
	rm -f $(OBJ) *.out *.core $(EXE)
