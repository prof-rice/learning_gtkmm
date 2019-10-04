CXXFLAGS = --std=c++17
GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`

all: hello

debug: CXXFLAGS += -g
debug: hello

hello: main.o
	$(CXX) $(CXXFLAGS) -o hello main.o $(GTKFLAGS)

main.o: main.cpp 
	$(CXX) $(CXXFLAGS) -c main.cpp $(GTKFLAGS)

clean:
	-rm -f *.o *.gch *~ hello
