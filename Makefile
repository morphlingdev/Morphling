# Compiler to use
CC=g++

CFLAGS=-c -lSDL -lSDL_ttf
LDFLAGS=-lSDL -lSDL_ttf -lSDL_image
SOURCES=Morphling.cpp Display.cpp Ability.cpp Map.cpp Tile.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Morphling

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS) $(EXECUTABLE)
