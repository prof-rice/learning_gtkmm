#include "scoop.h"

namespace Mice {

Scoop::Scoop(std::string name, std::string description, double cost, double price)
      : Item(name, description, cost, price) { }
Scoop::Scoop(std::istream& ist) {
    // The header must have been stripped from the incoming stream at this point
    getline(ist, _name);
    ist >> _cost; ist.ignore();
    ist >> _price; ist.ignore();
    ist >> _quantity; ist.ignore();
    getline(ist, _description);
}

void Scoop::save(std::ostream& ost) {
    ost << "#" << std::endl << "SCOOP" << std::endl; // header
    ost << _name << std::endl;
    ost << _cost << std::endl;
    ost << _price << std::endl;
    ost << _quantity << std::endl;
    ost << _description << std::endl;
}

std::string Scoop::type() const {return "Scoop";}

}
