#ifndef __ORDER_H
#define __ORDER_H

#include <vector>
#include "sweet.h"

class Order {
  public:
    void add(const int quantity, const Sweet& sweet);
    int size() const;
    int quantity(int index) const;
    Sweet sweet(int index) const;
    double price() const;
  private:
    std::vector<int> _quantities;
    std::vector<Sweet> _sweets;
};
std::ostream& operator<<(std::ostream& ost, const Order& order);
#endif
