CC=g++
CFLAGS=-c -Wall -std=c++11
SFML=./lib 
LDFLAGS=-L$(SFML) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SOURCES=main.cpp Ball.cpp Paddle.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=sfml-app

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS) $(EXECUTABLE)
