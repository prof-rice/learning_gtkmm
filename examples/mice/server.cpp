#include "server.h"

namespace Mice {
Server::Server(std::string name, std::string id, std::string phone, double salary)
             : Person(name, id, phone), _salary{salary}, _num_orders{0} { }
Server::Server(std::istream& ist) {
    // The header must have been stripped from the incoming stream at this point
    getline(ist, _name);
    getline(ist, _id);
    getline(ist, _phone);
    ist >> _salary; ist.ignore();
    ist >> _num_orders; ist.ignore();
}

void Server::save(std::ostream& ost) {
    ost << "#" << std::endl << "SERVER" << std::endl; // header
    ost << _name << std::endl;
    ost << _id << std::endl;
    ost << _phone << std::endl;
    ost << _salary << std::endl;
    ost << _num_orders << std::endl;
}

bool Server::fill_order_and_pay() {
    ++_num_orders;
    return (_num_orders % PAY_PERIOD) == 0;
}
bool Server::restock_and_pay() {
    _num_orders += 2;
    return ((_num_orders % PAY_PERIOD) == 0) 
       || (((_num_orders - 1) % PAY_PERIOD) == 0);
}
double Server::pay_server() { }
int Server::num_orders() {return _num_orders;}
int Server::salary() {return _salary;}
}
