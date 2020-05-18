#ifndef __STORE_H
#define __STORE_H

#include "order.h"

class Store{
  public:
    void add(Order& order);
    int num_orders();
    const Order& order(int number);

    void add(Sweet& sweet);
    int num_sweets();
    const Sweet& sweet(int number);
  private:
    std::vector<Sweet> _sweets;
    std::vector<Order> _orders;
};
#endif
