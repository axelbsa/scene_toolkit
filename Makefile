#LFLAGS=-lraylib -lopengl32 -lraylib -lglfw3 -lgdi32

CC=g++
LD=ld
CFLAGS=-O2 -Wall -std=c++11 -Wno-missing-braces -Isrc/ -Llib/
LFLAGS=-lraylib -lX11 -lXrandr -pthread -lXi -ldl -lXinerama -lXi -lXcursor -lGL -lGLU -lpthread -lrocket

# Windows LFLAGS
#LFLAGS=-lraylib -lopengl32 -lraylib -lglfw3 -lgdi32

OUT := ray

SOURCES := src/main.cpp src/scene_state_machine.cpp src/scenes/game_scene/scene_game.cpp src/scenes/splash_scene/splash_screen.cpp
SOBJS := $(SOURCES:%=$(BUILD_DIR)/%.o)

all:
	$(CC) $(SOURCES) $(CFLAGS) $(LFLAGS) -o $(OUT)

debug:
	$(CC) -g -DDEBUG $(SOURCES) -Wall -std=c++11 -Isrc/ -Llib/ $(LFLAGS) -o $(OUT)

clean:
	rm ray
