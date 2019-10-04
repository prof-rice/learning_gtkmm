# File: Makefile

CXXFLAGS = --std=c++17
GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`

all: clock

debug: CXXFLAGS += -g
debug: clock

clock: main.o mainwin.o
	$(CXX) $(CXXFLAGS) -o clock main.o mainwin.o $(GTKFLAGS)

main.o: main.cpp *.h
	$(CXX) $(CXXFLAGS) -c main.cpp $(GTKFLAGS)

mainwin.o: mainwin.cpp *.h
	$(CXX) $(CXXFLAGS) -c mainwin.cpp $(GTKFLAGS)

clean:
	-rm -f *.o *.gch *~ clock
