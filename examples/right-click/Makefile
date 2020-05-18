CXXFLAGS = --std=c++17
GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`

all: rightclick

mainwin.o: mainwin.cpp *.h
	$(CXX) $(CXXFLAGS) -c mainwin.cpp $(GTKFLAGS)

main.o: main.cpp *.h
	$(CXX) $(CXXFLAGS) -c main.cpp $(GTKFLAGS)

rightclick: mainwin.o main.o *.h
	$(CXX) $(CXXFLAGS) -o rightclick mainwin.o main.o $(GTKFLAGS)

clean:
	-rm -f *.gch *.o *~a.out ./register ./a.out

rebuild: clean all