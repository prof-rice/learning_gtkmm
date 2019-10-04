CXXFLAGS = --std=c++17
GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`

all: double-click

debug: CXXFLAGS += -g
debug: double-click

double-click: main.o main_window.o 
	$(CXX) $(CXXFLAGS) -o double-click main.o main_window.o $(GTKFLAGS)

main.o: main.cpp *.h
	$(CXX) $(CXXFLAGS) -c main.cpp $(GTKFLAGS)

main_window.o: main_window.cpp *.h
	$(CXX) $(CXXFLAGS) -c main_window.cpp $(GTKFLAGS)

clean:
	-rm -f *.o *.gch *~ double-click
