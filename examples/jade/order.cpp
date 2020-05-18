#include "order.h"
#include "java.h"
#include "donut.h"

int Order::_next_order_number = 0;

Order::Order(Customer* customer) : _order_number{_next_order_number++}, _customer{customer}, _is_paid{false}, _is_filled{false} { }
Order::Order(std::istream& ist) {
    int i;
    ist >> _order_number; ist.ignore();
    if(_order_number == 0) {
       ist >> _next_order_number; ist.ignore();
    }
    ist >> i; ist.ignore(); _is_paid = static_cast<bool>(i);
    ist >> i; ist.ignore(); _is_filled = static_cast<bool>(i);
    _customer = new Customer{ist};
    int products_size;
    ist >> products_size; ist.ignore();
    while(products_size--) {
       std::string product_type;
       std::getline(ist, product_type);
       if (product_type == "Java") _products.push_back(new Java{ist});
       else if (product_type == "Donut") _products.push_back(new Donut{ist});
       else throw std::runtime_error{"Bad product type: " + product_type};
    }
}
void Order::save(std::ostream& ost) {
    ost << _order_number << std::endl;
    if(_order_number == 0) {
        ost << _next_order_number << std::endl;
    }
    ost << static_cast<int>(_is_paid) << std::endl;
    ost << static_cast<int>(_is_filled) << std::endl;
    _customer->save(ost);
    ost << _products.size() << std::endl;
    for(Product* f : _products) {ost << f->type() << std::endl; f->save(ost);}
}

Customer* Order::customer() const {return _customer;}

int Order::order_number() const {return _order_number;}
void Order::add_product(Product* product) {_products.push_back(product);}

bool Order::paid() const {return _is_paid;}
void Order::pay() {_is_paid = true;}
bool Order::filled() const {return _is_filled;}
void Order::fill() {_is_filled = true;}

std::ostream& operator<<(std::ostream& ost, const Order& order) {
    ost << "Order #" << order._order_number << " (for " << *(order.customer()) << "):";
    std::string separator = "\n  ";
    for (auto p : order._products) {
        ost << separator << p->to_string();
    }
    return ost;
}

bool operator<(const Order& lhs, const Order& rhs) {
    return lhs.order_number() < rhs.order_number();
}
