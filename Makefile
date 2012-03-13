CC=g++
CFLAGS=-c `sdl-config --cflags`
LDFLAGS=`sdl-config --libs` -lSDL_ttf -lSDL_image
SOURCES=Morphling.cpp Display.cpp Ability.cpp Map.cpp Tile.cpp Entity.cpp MessageLog.cpp Item.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Morphling

all: $(SOURCES) $(EXECUTABLE)

debug: CFLAGS += -Wunused -DDEBUG -g
debug: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@  $(LDFLAGS)

.cpp.o:
	$(CC) $< -o $@ $(CFLAGS)

clean:
	rm $(OBJECTS) $(EXECUTABLE)
