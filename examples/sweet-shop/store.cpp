#include "store.h"

void Store::add(Order& order) {_orders.push_back(order);}
int Store::num_orders() {return _orders.size();}
const Order& Store::order(int number) {return _orders[number];}

void Store::add(Sweet& sweet) {_sweets.push_back(sweet);}
int Store::num_sweets() {return _sweets.size();}
const Sweet& Store::sweet(int number) {return _sweets[number];}

