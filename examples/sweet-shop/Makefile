CXXFLAGS += --std=c++17
GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`

all: sweets sweets-cli

sweets: main-gui.o mainwin.o order.o store.o sweet.o view.o *.h
	$(CXX) $(CXXFLAGS) main-gui.o mainwin.o order.o store.o sweet.o $(GTKFLAGS) -o sweets
sweets-cli:  main-cli.o controller.o order.o store.o sweet.o view.o *.h
	$(CXX) $(CXXFLAGS) main-cli.o controller.o view.o order.o store.o sweet.o -o sweets-cli
main-gui.o: main-gui.cpp *.h
	$(CXX) $(CXXFLAGS) -c main-gui.cpp $(GTKFLAGS) -o main-gui.o
mainwin.o: mainwin.cpp *.h
	$(CXX) $(CXXFLAGS) -c mainwin.cpp $(GTKFLAGS) -o mainwin.o
main-cli.o: main-cli.cpp *.h
	$(CXX) $(CXXFLAGS) -c main-cli.cpp -o main-cli.o
controller.o: controller.cpp *.h
	$(CXX) $(CXXFLAGS) -c controller.cpp -o controller.o
order.o: order.cpp *.h
	$(CXX) $(CXXFLAGS) -c order.cpp -o order.o
store.o: store.cpp *.h
	$(CXX) $(CXXFLAGS) -c store.cpp -o store.o
sweet.o: sweet.cpp *.h
	$(CXX) $(CXXFLAGS) -c sweet.cpp -o sweet.o
view.o: view.cpp *.h
	$(CXX) $(CXXFLAGS) -c view.cpp -o view.o
clean:
	rm -f *.o *.gch a.out sweets sweets-cli

