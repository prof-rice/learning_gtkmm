CXXFLAGS = --std=c++17
GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`

all: grid

debug: CXXFLAGS += -g
debug: grid

grid: main.o mainwin.o
	$(CXX) $(CXXFLAGS) -o grid main.o mainwin.o $(GTKFLAGS)

main.o: main.cpp *.h
	$(CXX) $(CXXFLAGS) -c main.cpp $(GTKFLAGS)

mainwin.o: mainwin.cpp *.h
	$(CXX) $(CXXFLAGS) -c mainwin.cpp $(GTKFLAGS)

clean:
	-rm -f *.o *.gch *~ grid
