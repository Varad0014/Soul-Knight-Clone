#OBJS specifies which files to compile as part of the project
#OBJS =  main.cpp Game.hpp Game.cpp TextureManager.hpp TextureManager.cpp GameObject.hpp GameObject.cpp
OBJS =  main.cpp Game.cpp TextureManager.cpp GameObject.cpp Player.cpp Map.cpp Camera.cpp Enemy.cpp MenuObject.cpp Bullet.cpp HealthBar.cpp EnemyHealth.cpp PlayerHealth.cpp #SDLEventManager.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
