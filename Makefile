# TARGET = launcher
# SRCS = launcher/src/main.cpp
# OBJS = $(SRCS:.cpp=.o)

# CXX = g++
# CXXFLAGS = -Wall -std=c++17 -I /usr/include/qt6 $(shell pkg-config --cflags Qt6Widgets)
# LDFLAGS = $(shell pkg-config --libs Qt6Widgets)

# $(TARGET): $(OBJS)
# 	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# clean:
# 	rm -f $(OBJS) $(TARGET)

LAUNCHER = _launcher
GAME = _game
LSRCS = launcher/src/main.cpp
GSRCS = game/src/main.cpp

all:
	g++ -Wall -I /usr/include/qt6 $(shell pkg-config --cflags Qt6Widgets) $(LSRCS) -o $(LAUNCHER) $(shell pkg-config --libs Qt6Widgets)
	g++ -Wall -lGL -lGLEW -lglfw $(GSRCS) -o $(GAME)
	chmod +x $(LAUNCHER) $(GAME)

clean:
	rm $(LAUNCHER)
	rm $(GAME)