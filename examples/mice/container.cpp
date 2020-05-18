#include "container.h"

namespace Mice {

Container::Container(std::string name, std::string description, double cost, double price,
              int max_scoops)
          : Item(name, description, cost, price), _max_scoops{max_scoops} { }
Container::Container(std::istream& ist) {
    // The header must have been stripped from the incoming stream at this point
    getline(ist, _name);
    ist >> _cost; ist.ignore();
    ist >> _price; ist.ignore();
    ist >> _quantity; ist.ignore();
    ist >> _max_scoops; ist.ignore();
    getline(ist, _description);
}
    
void Container::save(std::ostream& ost) {
    ost << "#" << std::endl << "CONTAINER" << std::endl; // header
    ost << _name << std::endl;
    ost << _cost << std::endl;
    ost << _price << std::endl;
    ost << _quantity << std::endl;
    ost << _max_scoops << std::endl;
    ost << _description << std::endl;
}
std::string Container::type() const {return "Container";}
int Container::max_scoops() const {return _max_scoops;}
}
