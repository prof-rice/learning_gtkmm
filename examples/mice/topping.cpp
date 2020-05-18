#include "topping.h"
#include <stdexcept>
#include <iostream>
#include <iomanip>

namespace Mice {

Topping::Topping(std::string name, std::string description, double cost, double price,
              int amount) :
    Item(name, description, cost, price), _amount{amount} { }

Topping::Topping(std::istream& ist) {
    // The header must have been stripped from the incoming stream at this point
    getline(ist, _name);
    ist >> _cost; ist.ignore();
    ist >> _price; ist.ignore();
    ist >> _quantity; ist.ignore();
    ist >> _amount; ist.ignore();
    getline(ist, _description);
}

void Topping::save(std::ostream& ost) {
    ost << "#" << std::endl << "TOPPING" << std::endl; // header
    ost << _name << std::endl;
    ost << _cost << std::endl;
    ost << _price << std::endl;
    ost << _quantity << std::endl;
    ost << _amount << std::endl;
    ost << _description << std::endl;
}

std::string Topping::type() const {return "Topping";}
int Topping::amount() const {return _amount;}
void Topping::set_amount(int amount) {
    if (0 < amount && amount < 5) _amount = amount;
    else throw std::runtime_error("Invalid topping amount");
}

std::string Topping::show_server() const {
    if (_amount == LIGHT_AMOUNT) return _name + " (light)";
    else if (_amount == NORMAL_AMOUNT) return _name;
    else if (_amount == EXTRA_AMOUNT) return _name + " (extra)";
    else if (_amount == DRENCHED_AMOUNT) return _name + " (drenched)";
    else throw std::runtime_error("Invalid topping amount in Topping::show_server()");
}

}

