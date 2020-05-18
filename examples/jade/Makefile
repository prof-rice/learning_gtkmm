# Suggested Makefile for CSE_1325 Homework #12
CXXFLAGS += --std=c++17
GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`

default: jade

all: main 

debug: CXXFLAGS += -g
debug: default

jade: main.o mainwin.o mainwin-on_create_order_click.o mainwin-on_create_java_click.o mainwin-on_create_donut_click.o store.o order.o product.o java.o donut.o customer.o *.h
	${CXX} ${CXXFLAGS} -o jade main.o mainwin.o mainwin-on_create_order_click.o mainwin-on_create_java_click.o mainwin-on_create_donut_click.o store.o order.o product.o java.o donut.o customer.o $(GTKFLAGS)
main.o: main.cpp *.h
	${CXX} ${CXXFLAGS} -c main.cpp $(GTKFLAGS)
mainwin.o: mainwin.cpp *.h
	${CXX} ${CXXFLAGS} -c mainwin.cpp $(GTKFLAGS)
mainwin-on_create_order_click.o: mainwin-on_create_order_click.cpp *.h
	${CXX} ${CXXFLAGS} -c mainwin-on_create_order_click.cpp $(GTKFLAGS)
mainwin-on_create_java_click.o: mainwin-on_create_java_click.cpp *.h
	${CXX} ${CXXFLAGS} -c mainwin-on_create_java_click.cpp $(GTKFLAGS)
mainwin-on_create_donut_click.o: mainwin-on_create_donut_click.cpp *.h
	${CXX} ${CXXFLAGS} -c mainwin-on_create_donut_click.cpp $(GTKFLAGS)
store.o: store.cpp *.h
	${CXX} ${CXXFLAGS} -c store.cpp
order.o: order.cpp *.h
	${CXX} ${CXXFLAGS} -c order.cpp
product.o: product.cpp *.h
	${CXX} ${CXXFLAGS} -c product.cpp
java.o: java.cpp *.h
	${CXX} ${CXXFLAGS} -c java.cpp
donut.o: donut.cpp *.h
	${CXX} ${CXXFLAGS} -c donut.cpp
customer.o: customer.cpp *.h
	${CXX} ${CXXFLAGS} -c customer.cpp
clean:
	-rm -f *.gch *.o a.out jade 
