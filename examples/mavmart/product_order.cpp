#include "product_order.h"
#include <iomanip>

Product_order::Product_order(std::string name, double price, int quantity)
    : Product{name, price}, _quantity{quantity} {}
Product_order::Product_order(Product product, int quantity)
    : Product{product}, _quantity{quantity} {}
Product_order::Product_order(std::istream& ist) 
    : Product{ist} {
    ist >> _quantity; ist.ignore();
}
void Product_order::save(std::ostream& ost) {
    Product::save(ost);
    ost << _quantity << '\n';
}
int Product_order::quantity() const {return _quantity;}
double Product_order::cost() const {return price() * _quantity;}
bool Product_order::operator==(const Product_order& po) {
    return ((name()     == po.name())  &&
            (price()    == po.price()) && 
            (quantity() == po.quantity()));
}
bool Product_order::operator!=(const Product_order& po) {return !(*this == po);}
std::ostream& operator<<(std::ostream& ost, const Product_order& po) {
    ost << po.name() << " (" << po._quantity << " @ $" << std::fixed << std::setprecision(2) << po.price() << " = $" << po.cost() << ')';
    return ost;
}
