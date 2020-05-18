#compiler options
CXXFLAGS+=--std=c++11

#source files
SOURCES=$(wildcard *.cpp)

#object files
OBJECTS=$(SOURCES:.cpp=.o)

#main link objects
MOBJECTS=$(filter-out test%,$(OBJECTS))

#test link objects
TOBJECTS=$(filter-out main.o,$(OBJECTS))

#included libraries
INCLUDE=`/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`

#executable filename
EXECUTABLE=mice

all: div $(EXECUTABLE)

#Special symbols used:
#$^ - is all the dependencies (in this case =$(OBJECTS) )
#$@ - is the result name (in this case =$(EXECUTABLE) )

$(EXECUTABLE): $(MOBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(INCLUDE)

test: CXXFLAGS+= -g
test: $(TOBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(INCLUDE)

debug: CXXFLAGS+= -g
debug: div $(EXECUTABLE)

%.o: %.cpp *.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	-rm -f $(EXECUTABLE) test $(OBJECTS)

div:
	@test -x ~/bin/div && div
	@echo
	@echo 'X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-'
	@echo '-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X'
	@echo 'X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-'
	@echo '-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X'
	@echo

