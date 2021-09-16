#OBJS= main.cpp game.cpp object.cpp audio.cpp"

OBJS = *.cpp

CC = g++

INCLUDE_PATHSZ = -IC:\Users\PickP\Desktop\Programming\Projects\FPT\FPT\include

INCLUDE_PATHS = -IC:\SL\include\SDL2

INCLUDE_PATHSM = -IC:\mingw64\include

LIBRARY_PATHS = -LC:\SL\lib

COMPILER_FLAGS = -w -Wl,-subsystem,windows

LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

OBJ_NAME = main
all : $(OBJS)
	$(CC) $(OBJS) $(GFX) $(INCLUDE_PATHSM) $(INCLUDE_PATHS) $(INCLUDE_PATHSZ) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)