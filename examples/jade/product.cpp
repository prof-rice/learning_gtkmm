#include "product.h"
#include <sstream>
#include <iostream>
#include <iomanip>

Product::Product(std::string name, double price, double cost)
    : _name{name}, _price{price}, _cost{cost} { }

Product::Product(std::istream& ist) {
    std::getline(ist, _name);
    ist >> _price; ist.ignore();
    ist >> _cost; ist.ignore();
}
void Product::save(std::ostream& ost){
    ost << _name << std::endl;
    ost << _price << std::endl;
    ost << _cost << std::endl;
}

std::string Product::name() {return _name;}
std::string Product::type() {return "Product";}

std::string Product::to_string() {
    std::ostringstream oss;
    oss << _name << std::fixed << std::setprecision(2) << " ($" << _price << " / $" << _cost << ')';
    return oss.str();
}
