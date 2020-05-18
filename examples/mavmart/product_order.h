#ifndef __PRODUCT_ORDER_H
#define __PRODUCT_ORDER_H

#include "product.h"
#include <fstream>

class Product_order : public Product {
  public:
    Product_order(std::string name, double price, int quantity);
    Product_order(Product product, int quantity);
    Product_order(std::istream& ist);
    void save(std::ostream& ost);
    int quantity() const;
    double cost() const;
    bool operator==(const Product_order& po);
    bool operator!=(const Product_order& po);
    friend std::ostream& operator<<(std::ostream& ost, const Product_order& po);
  private:
    int _quantity;
};
#endif
