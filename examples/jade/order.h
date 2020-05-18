#pragma once
#include "product.h"
#include "customer.h"
#include <vector>

class Order {
  public:
    Order(Customer* customer);
    Order(std::istream& ist);
    virtual void save(std::ostream& ost);
    Customer* customer() const;
    int order_number() const;
    void add_product(Product* product);
    bool paid() const;
    void pay();
    bool filled() const;
    void fill();
    friend std::ostream& operator<<(std::ostream& ost, const Order& order);
  protected:
    std::vector<Product*> _products;
  private:
    static int _next_order_number;
    int _order_number; 
    Customer* _customer;
    bool _is_paid;
    bool _is_filled;
};

bool operator<(const Order& lhs, const Order& rhs);
