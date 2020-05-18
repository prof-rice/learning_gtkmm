#include "customer.h"

namespace Mice {
Customer::Customer(std::string name, std::string id, std::string phone)
             : Person(name, id, phone) { }
Customer::Customer(std::istream& ist) {
    // The header must have been stripped from the incoming stream at this point
    getline(ist, _name);
    getline(ist, _id);
    getline(ist, _phone);
}

void Customer::save(std::ostream& ost) {
    ost << "#" << std::endl << "CUSTOMER" << std::endl; // header
    ost << _name << std::endl;
    ost << _id << std::endl;
    ost << _phone << std::endl;
}

}
