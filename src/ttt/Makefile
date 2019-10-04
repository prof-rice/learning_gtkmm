CXXFLAGS = --std=c++17 -fPIC
# -fPIC works around a g++ issue with Position Independent Code
GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`

all: ttt

debug: CXXFLAGS += -g
debug: ttt

ttt: main.o mainwin.o
	$(CXX) $(CXXFLAGS) -o ttt main.o mainwin.o $(GTKFLAGS)

main.o: main.cpp *.h
	$(CXX) $(CXXFLAGS) -c main.cpp $(GTKFLAGS)

mainwin.o: mainwin.cpp *.h
	$(CXX) $(CXXFLAGS) -c mainwin.cpp $(GTKFLAGS)

clean:
	-rm -f *.o *.gch *~ ttt
