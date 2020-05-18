#pragma once
#include <string>
#include <ostream>
#include <istream>

class Product {
  public:
    Product(std::string name, double price, double cost);
    std::string name();
    virtual std::string type();
    virtual std::string to_string();
    Product(std::istream& ist);
    virtual void save(std::ostream& ost);
  protected:
    std::string _name;
    double _price;
    double _cost;
};
