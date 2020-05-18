#ifndef __ORDER_H
#define __ORDER_H

#include "product_order.h"
#include <vector>
#include <fstream>

class Order {
  public:
    Order(std::string email);
    Order(std::istream& ist);
    void save(std::ostream& ost);
    std::string email() const;
    double cost() const;
    void add_product_order(Product_order po);
    int num_product_orders();
    Product_order product_order(int index);
    friend std::ostream& operator<<(std::ostream& ost, const Order& order);
  private:
    std::string _email;
    std::vector<Product_order> _products;
};
#endif
