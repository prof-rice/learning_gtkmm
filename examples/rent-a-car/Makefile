# Suggested Makefile for CSE_1325 Homework #7 full_credit
CXXFLAGS += --std=c++17
GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
default: main

method: cp_method main

cp_method:
	cp mainwin_method.h mainwin.h
	cp mainwin_method.cpp mainwin.cpp

lambda: cp_lambda main

cp_lambda:
	cp mainwin_lambda.h mainwin.h
	cp mainwin_lambda.cpp mainwin.cpp

all: main test_rental_site test_vehicle test_renter

debug: CXXFLAGS += -g
debug: default

main: main.o mainwin.o controller.o view.o rental_site.o vehicle.o renter.o dialogs.o *.h
	${CXX} ${CXXFLAGS} -o main main.o mainwin.o controller.o view.o rental_site.o vehicle.o renter.o dialogs.o $(GTKFLAGS)
main.o: main.cpp *.h
	${CXX} ${CXXFLAGS} -c main.cpp $(GTKFLAGS)
mainwin.o: mainwin.cpp *.h
	${CXX} ${CXXFLAGS} -c mainwin.cpp $(GTKFLAGS)
controller.o: controller.cpp *.h
	${CXX} ${CXXFLAGS} -c controller.cpp $(GTKFLAGS)
view.o: view.cpp *.h
	${CXX} ${CXXFLAGS} -c view.cpp
rental_site.o: rental_site.cpp *.h
	${CXX} ${CXXFLAGS} -c rental_site.cpp
vehicle.o: vehicle.cpp *.h
	${CXX} ${CXXFLAGS} -c vehicle.cpp
renter.o: renter.cpp *.h
	${CXX} ${CXXFLAGS} -c renter.cpp
dialogs.o: dialogs.cpp *.h
	${CXX} ${CXXFLAGS} -c dialogs.cpp $(GTKFLAGS)
test_rental_site: test_rental_site.o rental_site.o vehicle.o renter.o *.h
	${CXX} ${CXXFLAGS} -o test_rental_site test_rental_site.o rental_site.o vehicle.o renter.o
test_rental_site.o: test_rental_site.cpp *h
	${CXX} ${CXXFLAGS} -c test_rental_site.cpp
test_vehicle: test_vehicle.o vehicle.o renter.o *.h
	${CXX} ${CXXFLAGS} -o test_vehicle test_vehicle.o vehicle.o renter.o
test_vehicle.o: test_vehicle.cpp *h
	${CXX} ${CXXFLAGS} -c test_vehicle.cpp
test_renter: test_renter.o renter.o  *.h
	${CXX} ${CXXFLAGS} -o test_renter test_renter.o renter.o 
test_renter.o: test_renter.cpp *h
	${CXX} ${CXXFLAGS} -c test_renter.cpp
clean:
	-rm -f *.gch *.o main test_rental_site test_vehicle test_renter
