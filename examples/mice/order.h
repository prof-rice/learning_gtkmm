#ifndef _ORDER_H
#define _ORDER_H

#include "serving.h"
#include "customer.h"
#include "server.h"
#include <vector>
#include <iostream>
#include <fstream>

namespace Mice {

enum class Order_state {Unfilled, Filled, Paid, Canceled};
enum class Order_event {Fill, Pay, Cancel};

class Order {
  public:
    Order(Customer customer, int order_number);
    Order(std::istream& ist);
    void save(std::ostream& ost);

    void add_serving(Serving serving);
    std::vector<Serving> servings() const;

    void fill(Server server);
    void pay();
    void cancel();

    int id() const;
    double cost() const;
    double price() const;
    Order_state state() const;
    void process_event(Order_event event, Server server = Server{"TBD", "TBD", "TBD", 0});
    std::string show_server() const;
  private:
    int _id;
    Customer _customer{"", "", ""};
    Server _server{"TBD", "TBD", "TBD", 0};
    Order_state _state;
    std::vector<Serving> _servings;
};

}

std::ostream& operator<<(std::ostream& os, const Mice::Order& order);

#endif
