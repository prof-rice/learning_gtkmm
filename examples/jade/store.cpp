#include "store.h"
#include "java.h"
#include "donut.h"
#include "to_string.h"

Store::Store(std::string store_name) : _name{store_name} { }
std::string Store::name() {return _name;}

Store::Store(std::istream& ist) {
    std::string s;
    std::getline(ist, s);
    if (s != program_name) throw std::runtime_error{"Not a " + program_name + " file"};
    std::string file_version;
    std::getline(ist, file_version);
    if (file_version != "0.3.0"
     && file_version != program_version) throw std::runtime_error{"Incompatible file version " + s + "(should be " + program_version + ")"};
    std::getline(ist, _name);
    int products_size;
    ist >> products_size; ist.ignore();
    while(products_size--) {
       std::string product_type;
       std::getline(ist, product_type);
       if (product_type == "Java") _products.push_back(new Java{ist});
       else if (product_type == "Donut") _products.push_back(new Donut{ist});
       else throw std::runtime_error{"Bad product type: " + product_type};
    }
    int customers_size;
    ist >> customers_size; ist.ignore();
    while(customers_size--) _customers.push_back(new Customer{ist});
    if(file_version == program_version) {  // Earlier file versions lacked order data
        int orders_size;
        ist >> orders_size; ist.ignore();
        while(orders_size--) _orders.push_back(new Order{ist});
    }
}
void Store::save(std::ostream& ost) {
    ost << program_name << '\n' << program_version << '\n';
    ost << _name << std::endl;
    ost << _products.size() << std::endl;
    for(Product* f : _products) {ost << f->type() << std::endl; f->save(ost);}
    ost << _customers.size() << std::endl;
    for(Customer* c : _customers) c->save(ost);
    ost << _orders.size() << std::endl;
    for(Order* o : _orders) o->save(ost);
}

void Store::place_order(Order* order) {_orders.push_back(order);} // Places a new order
int Store::number_of_orders() {return _orders.size(); } // # of orders defined
std::string Store::order_to_string(int order_number) {return to_string(*_orders[order_number]);}

void Store::add_product(Product* product) {_products.push_back(product);}
int Store::number_of_products() {return _products.size();}
Product* Store::get_product(int product) {return _products[product];}
std::string Store::product_to_string(int product) {
    std::ostringstream oss;
    oss << _products[product]->to_string(); // Access the string representation polymorphically!
    return oss.str();
}

void Store::add_customer(Customer* customer) {_customers.push_back(customer);}
Customer* Store::get_customer(int customer) {return _customers[customer];}
int Store::number_of_customers() {return _customers.size();}
std::string Store::customer_to_string(int customer) {return to_string(*_customers[customer]);}

std::ostream& operator<<(std::ostream& ost, Store& store) {
    ost << "Store " << store._name << std::endl << std::endl;
    ost << "Products: " << std::endl;
    for (auto p : store._products) ost << "  " << p->to_string() << std::endl;
    return ost;
}
