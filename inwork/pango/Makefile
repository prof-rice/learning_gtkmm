CXXFLAGS = --std=c++17
GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`

all: guesser

debug: CXXFLAGS += -g
debug: guesser

guesser: main.o mainwin.o
	$(CXX) $(CXXFLAGS) main.o mainwin.o $(GTKFLAGS) -o guesser

main.o: main.cpp *.h
	$(CXX) $(CXXFLAGS) -c main.cpp $(GTKFLAGS) -o main.o

mainwin.o: mainwin.cpp *.h
	$(CXX) $(CXXFLAGS) -c mainwin.cpp $(GTKFLAGS) -o mainwin.o

clean:
	-rm -f *.o *.gch guesser
