CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
INCLUDES = -Ilib/pdcurses
LIBS = -Llib/pdcurses/wincon -lpdcurses
TARGET = build/game.exe
SRC = src/main.cpp src/map.cpp src/map.hpp src/display.cpp src/display.hpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(INCLUDES) $(LIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)