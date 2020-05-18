#include "donut.h"

Donut::Donut(std::string name, double price, double cost, Frosting frosting, bool sprinkles, Filling filling)
    : Product{name, price, cost}, _frosting{frosting}, _sprinkles{sprinkles}, _filling{filling} { }
Donut::Donut(std::istream& ist) : Product{ist} {
    int i;
    ist >> i; ist.ignore(); _frosting = static_cast<Frosting>(i);
    ist >> i; ist.ignore(); _sprinkles = static_cast<bool>(i);
    ist >> i; ist.ignore(); _filling = static_cast<Filling>(i);
}
    
void Donut::save(std::ostream& ost) {
    Product::save(ost);
    ost << static_cast<int>(_frosting) << std::endl;
    ost << static_cast<int>(_sprinkles) << std::endl;
    ost << static_cast<int>(_filling) << std::endl;
}
std::string Donut::type() {return "Donut";}
std::string Donut::to_string() {
    std::string result = Product::to_string();
    std::string separator = " (";
    std::string terminator = "";
    if (_frosting != Unfrosted) {
        result += separator + "frosted with " + frosting_to_string[_frosting];
        if (_sprinkles) result += " and sprinkles";
        separator = ", ";
        terminator = ")";
    }
    if (_filling != Unfilled) {
        result += separator + "filled with " + filling_to_string[_filling];
        terminator = ")";
    }
    result += terminator;
    return result;
}
