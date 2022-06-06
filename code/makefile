#OBJS specifies which files to compile as part of the project
OBJS =main.cpp bird.cpp text_input.cpp pipes.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = 

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2
#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = flappy
BIN_DIR= ../bin
SDL_DIRECTORY= -I../include/
#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(SDL_DIRECTORY)  -o $(OBJ_NAME) $(LINKER_FLAGS)