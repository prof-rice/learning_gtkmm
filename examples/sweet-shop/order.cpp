#include "order.h"

void Order::add(const int quantity, const Sweet& sweet) {
    _quantities.push_back(quantity);
    _sweets.push_back(sweet);
}
int Order::size() const {return _sweets.size();}
int Order::quantity(int index) const {
    if (0 > index >= _quantities.size()) throw std::out_of_range{"Index out of range"};
    return _quantities[index];
}
Sweet Order::sweet(int index) const {
    if (0 > index >= _sweets.size()) throw std::out_of_range{"Index out of range"};
    return _sweets[index];
}
double Order::price() const {
    double p = 0.0;
    for(int i=0; i<_sweets.size(); ++i) p += _quantities[i] * _sweets[i].price();
    return p;
}
std::ostream& operator<<(std::ostream& ost, const Order& order) {
    for(int i=0; i < order.size(); ++i) 
        ost << order.quantity(i) << " " << order.sweet(i) << '\n';
    return ost;
}
