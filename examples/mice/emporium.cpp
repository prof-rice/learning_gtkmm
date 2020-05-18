#include "emporium.h"
#include <stdexcept>

namespace Mice {

Emporium::Emporium(std::string name) : _name{name}, _cash_register{0}, _id{0} { }
Emporium::Emporium(std::istream& ist) {
    // WARNING: Do NOT strip the header - pass the FULL FILE to Emporium!
    std::string header1, header2;

    std::getline(ist, header1); // magic cookie
    std::getline(ist, header2);
    if (header1 != "MICE") throw std::runtime_error("NOT an Emporium file");
    if (header2 != "0.1") throw std::runtime_error("Incompatible file version");
 
    std::getline(ist, header1); // header
    std::getline(ist, header2);
    if (header1 != "#") throw std::runtime_error("No Emporium records in file");
    if (header2 != "EMPORIUM") throw std::runtime_error("Malformed Emporium record");

    std::getline(ist, _name);
    ist >> _cash_register; ist.ignore();
    ist >> _id; ist.ignore();

    while(ist) {
        std::getline(ist, header1); // header
        std::getline(ist, header2);

        if (header1 != "#") throw std::runtime_error("missing # during input");
        if (header2 == "CONTAINER") _containers.push_back(Container{ist});
        else if (header2 == "SCOOP") _scoops.push_back(Scoop{ist});
        else if (header2 == "TOPPING") _toppings.push_back(Topping{ist});
        else if (header2 == "ORDER") _orders.push_back(Order{ist});
        else if (header2 == "SERVER") _servers.push_back(Server{ist});
        else if (header2 == "CUSTOMER") _customers.push_back(Customer{ist});
        else if (header2 == "END EMPORIUM") break;
        else throw std::runtime_error("invalid item type in Emporium");
    }
}

void Emporium::save(std::ostream& ost) {
        ost << "MICE" << std::endl << "0.1" << std::endl; // magic cookie
        ost << "#" << std::endl << "EMPORIUM" << std::endl; // header
        ost << _name << std::endl;
        ost << _cash_register << std::endl;
        ost << _id << std::endl;

        for (Mice::Container c : _containers) c.save(ost);
        for (Mice::Scoop s : _scoops) s.save(ost);
        for (Mice::Topping t : _toppings) t.save(ost);
        for (Mice::Order o : _orders) o.save(ost);
        for (Mice::Server s : _servers) s.save(ost);
        for (Mice::Customer c : _customers) c.save(ost);
        ost << "#" << std::endl << "END EMPORIUM" << std::endl; // footer
}

std::string Emporium::name() {return _name;}
double Emporium::cash_register() {return _cash_register;}
void Emporium::debit(double amount) {_cash_register -= amount;}
void Emporium::credit(double amount) {_cash_register += amount;}
int Emporium::next_id() {return ++_id;}

int Emporium::num_containers() {return _containers.size();}
int Emporium::num_scoops() {return _scoops.size();}
int Emporium::num_toppings() {return _toppings.size();}
int Emporium::num_orders() {return _orders.size();}
int Emporium::num_servers() {return _servers.size();}
int Emporium::num_customers() {return _customers.size();}

Container& Emporium::container(int index) {return _containers[index];}
Scoop& Emporium::scoop(int index) {return _scoops[index];}
Topping& Emporium::topping(int index) {return _toppings[index];}
Order& Emporium::order(int index) {return _orders[index];}
Server& Emporium::server(int index) {return _servers[index];}
Customer& Emporium::customer(int index) {return _customers[index];}

void Emporium::add_container(Container container) {_containers.push_back(container);}
void Emporium::add_scoop(Scoop scoop) {_scoops.push_back(scoop);}
void Emporium::add_topping(Topping topping) {_toppings.push_back(topping);}
void Emporium::add_order(Order order) {_orders.push_back(order);}
void Emporium::add_server(Server server) {_servers.push_back(server);}
void Emporium::add_customer(Customer customer) {_customers.push_back(customer);}

// std::vector<Mice::Container>& Emporium::containers() {return _containers;}
// std::vector<Mice::Scoop>& Emporium::scoops() {return _scoops;}
// std::vector<Mice::Topping>& Emporium::toppings() {return _toppings;}
// std::vector<Mice::Order>& Emporium::orders() {return _orders;}
// std::vector<Mice::Server>& Emporium::servers() {return _servers;}
// std::vector<Mice::Customer>& Emporium::customers() {return _customers;}

}
