#include "sweet.h"
#include <iomanip>

Sweet::Sweet(std::string name, double price)
    : _name{name}, _price{price} { }
std::string Sweet::name() const {return _name;}
double Sweet::price() const {return _price;}
std::ostream& operator<<(std::ostream& ost, const Sweet& sweet) {
    ost << sweet.name() << " ($" << std::fixed << std::setprecision(2) << sweet.price() << ")";
    return ost;
}

