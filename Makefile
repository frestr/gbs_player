CXX=g++
CPPFLAGS=-Wall -Wextra -g -std=c++11 -c
LDFLAGS=
LDLIBS=-lpthread -lao

SRCS=$(wildcard src/*.cpp)
OBJS=$(notdir $(SRCS:.cpp=.o))

all: player

player: $(OBJS)
	$(CXX) -o player $(OBJS) $(LDLIBS)

%.o: src/%.cpp
	$(CXX) $(LDFLAGS) $(CPPFLAGS) $< 

clean:
	$(RM) $(OBJS)
