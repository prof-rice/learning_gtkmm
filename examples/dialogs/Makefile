CXXFLAGS += -std=c++17
GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`

all: hello gui cli test 

debug: CXXFLAGS += -g
debug: rebuild

rebuild: clean all

hello: hello.o
	$(CXX) $(CXXFLAGS) -o hello hello.cpp $(GTKFLAGS)
hello.o: hello.cpp
	$(CXX) $(CXXFLAGS) -c hello.cpp $(GTKFLAGS)

gui: guesser_gui.o dialogs.o
	$(CXX) $(CXXFLAGS) -o gui guesser_gui.o dialogs.o $(GTKFLAGS)
guesser_gui.o: guesser_gui.cpp *.h
	$(CXX) $(CXXFLAGS) -c guesser_gui.cpp $(GTKFLAGS)

cli: guesser_cli.cpp *.h
	$(CXX) $(CXXFLAGS) -o cli guesser_cli.cpp

test: test_dialogs.o dialogs.o *.h
	$(CXX) $(CXXFLAGS) -o test test_dialogs.cpp dialogs.o $(GTKFLAGS)
	./test 2> /dev/null

test_dialogs.o: test_dialogs.cpp *.h
	$(CXX) $(CXXFLAGS) -c test_dialogs.cpp $(GTKFLAGS)

dialogs.o: dialogs.cpp *.h
	$(CXX) $(CXXFLAGS) -c dialogs.cpp $(GTKFLAGS)

clean:
	-rm -f *.o *.gch *~ gui cli test hello
