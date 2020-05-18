#ifndef _SERVING_H
#define _SERVING_H

#include "container.h"
#include "scoop.h"
#include "topping.h"
#include <vector>
#include <iostream>
#include <fstream>

namespace Mice {

class Serving {
  public:
    Serving(Container container);
    Serving(std::istream& ist);
    void save(std::ostream& ost);
    void add_scoop(Scoop scoop);
    void add_topping(Topping topping);
    Container container() const;
    std::vector<Scoop> scoops() const;
    std::vector<Topping> toppings() const;
    double cost() const;
    double price() const;
    std::string show_server() const;
  private:
    Container _container{"", "", 0, 0, 0};
    std::vector<Scoop> _scoops;
    std::vector<Topping> _toppings;
};

}

std::ostream& operator<<(std::ostream& os, const Mice::Serving& serving);

#endif
