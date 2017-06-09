#LFLAGS=-lraylib -lopengl32 -lraylib -lglfw3 -lgdi32

CC=g++
CFLAGS=-O2 -Wall -std=c++11 -Wno-missing-braces
# LFLAGS=-lraylib -lGL -lraylib -lglfw3 -lX11 -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl
#LFLAGS=-lraylib -lglfw3 -lX11 -lXxf86vm -lXrandr -pthread -lXi -ldl -lXinerama -lXi -lXcursor -lGL -lGLU -lpthread

# Windows LFLAGS
LFLAGS=-lraylib -lopengl32 -lraylib -lglfw3 -lgdi32

SOURCES=main.cpp

all:
	$(CC) $(SOURCES) $(CFLAGS) $(LFLAGS) -o ray

debug:
	$(CC) -DDEBUG $(SOURCES) $(CFLAGS) $(LFLAGS) -o ray

clean:
	del ray
