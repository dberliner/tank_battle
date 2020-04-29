SOURCES := main.cpp
OBJS := $(SOURCES:.cpp=.o)
LFLAGS += -lSDL -lSDL_ttf
all: main

# Compile the binary 't' by calling the compiler with cflags, lflags, and any libs (if defined) and the list of objects.
main: $(OBJS)
	$(CXX) $(CFLAGS) -o tank_battle $(OBJS) $(LFLAGS) $(LIBS)

clean:
	rm -rf tank_battle *.o