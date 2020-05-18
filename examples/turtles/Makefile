CXXFLAGS += --std=c++17
GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`

all: star 

debug: CXXFLAGS += -g
debug: rebuild

rebuild: clean all

star: main.o mainwin.o line.o turtlepad.o *.h
	$(CXX) $(CXXFLAGS) main.o mainwin.o line.o turtlepad.o $(GTKFLAGS) -o star
main.o: main.cpp *.h
	$(CXX) $(CXXFLAGS) -c main.cpp $(GTKFLAGS) -o main.o
mainwin.o: mainwin.cpp *.h
	$(CXX) $(CXXFLAGS) -c mainwin.cpp $(GTKFLAGS) -o mainwin.o
turtlepad.o: turtlepad.cpp *.h
	$(CXX) $(CXXFLAGS) -c turtlepad.cpp $(GTKFLAGS) -o turtlepad.o
line.o: line.cpp *.h
	$(CXX) $(CXXFLAGS) -c line.cpp -o line.o
clean:
	rm -f *.o *.gch star 
