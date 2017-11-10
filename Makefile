CXX=g++
CPPFLAGS=-Wall -Wextra -g -std=c++11 -c
LDFLAGS=
LDLIBS=-lpthread -lao

SRCS=$(wildcard src/*.cpp)
OBJS=$(notdir $(SRCS:.cpp=.o))

all: player

debug: CPPFLAGS += -DDEBUG -I../gbz80-disasm
debug: LDLIBS += -L../gbz80-disasm -ldisasm
debug: player

player: $(OBJS)
	$(CXX) -o player $(OBJS) $(LDLIBS)

%.o: src/%.cpp
	$(CXX) $(LDFLAGS) $(CPPFLAGS) $< 

clean:
	$(RM) $(OBJS)
