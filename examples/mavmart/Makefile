# Suggested Makefile for CSE_1325 Homework #7 full_credit
CXXFLAGS += --std=c++17
FSFLAGS = -lstdc++fs
GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`

all: mavmart

debug: CXXFLAGS += -g
debug: all

test: CXXFLAGS += -g
test: test_product test_product_order test_order test_store

mavmart: main.o main_window.o controller.o view.o store.o order.o product.o product_order.o dialogs.o *.h
	${CXX} ${CXXFLAGS} -o mavmart main.o main_window.o controller.o view.o store.o order.o product.o product_order.o dialogs.o $(FSFLAGS) $(GTKFLAGS)
main.o: main.cpp *.h
	${CXX} ${CXXFLAGS} -c main.cpp $(GTKFLAGS)
main_window.o: main_window.cpp *.h
	${CXX} ${CXXFLAGS} -c main_window.cpp $(GTKFLAGS)
controller.o: controller.cpp *.h
	${CXX} ${CXXFLAGS} -c controller.cpp $(GTKFLAGS)
view.o: view.cpp *.h
	${CXX} ${CXXFLAGS} -c view.cpp
store.o: store.cpp *.h
	${CXX} ${CXXFLAGS} -c store.cpp
order.o: order.cpp *.h
	${CXX} ${CXXFLAGS} -c order.cpp
product.o: product.cpp *.h
	${CXX} ${CXXFLAGS} -c product.cpp
product_order.o: product_order.cpp *.h
	${CXX} ${CXXFLAGS} -c product_order.cpp
dialogs.o: dialogs.cpp *.h
	${CXX} ${CXXFLAGS} -c dialogs.cpp  $(GTKFLAGS)

test_product: test_product.o product.o *.h
	${CXX} ${CXXFLAGS} -o test_product test_product.o product.o
	-./test_product
test_product.o: test_product.cpp *.h
	${CXX} ${CXXFLAGS} -c test_product.cpp

test_product_order: test_product_order.o product_order.o product.o *.h
	${CXX} ${CXXFLAGS} -o test_product_order test_product_order.o product_order.o product.o
	-./test_product_order
test_product_order.o: test_product_order.cpp *.h
	${CXX} ${CXXFLAGS} -c test_product_order.cpp

test_order: test_order.o order.o product_order.o product.o *.h
	${CXX} ${CXXFLAGS} -o test_order test_order.o order.o product_order.o product.o
	-./test_order
test_order.o: test_order.cpp *.h
	${CXX} ${CXXFLAGS} -c test_order.cpp

test_store: test_store.o store.o order.o product_order.o product.o *.h
	${CXX} ${CXXFLAGS} -o test_store test_store.o store.o order.o product_order.o product.o
	-./test_store
test_store.o: test_store.cpp *.h
	${CXX} ${CXXFLAGS} -c test_store.cpp

clean:
	-rm -f *.gch *.o *~ a.out mavmart test_product test_product_order test_order test_store
