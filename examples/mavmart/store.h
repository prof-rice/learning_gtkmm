#ifndef __STORE_H
#define __STORE_H

#include "order.h"
#include <vector>

class Store {
  public:
    Store(std::string name);
    Store(std::istream& ist);
    void save(std::ostream& ost);
    std::string name() const;

    // Product Management
    void add_product(Product product);
    int num_products() const;
    Product product(int index) const;

    // Order Management
    int create_order(std::string email);
    void add_to_order(int order_num, Product_order po);
    int num_orders() const;
    Order order(int order_num) const;

    friend std::ostream& operator<<(std::ostream& ost, const Store& store);
  private:
    std::string _name;
    std::vector<Product> _products;
    std::vector<Order> _orders;
};

#endif
