CC=g++
CFLAGS=-std=c++11 -O3
LIBS=-lSDL2 -lSDL2_image -ltbb
SRC=SDL_init.cc Filters.cc Utils.cc Main.cc
OBJ=$(SRC:.cc=.o)
EXE=coca

all:
	$(CC) $(CFLAGS) -o $(EXE) $(SRC) $(LIBS)

clean:
	rm -f $(OBJ) *.out *.core $(EXE)
