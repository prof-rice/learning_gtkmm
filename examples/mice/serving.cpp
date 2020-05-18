#include "serving.h"
#include <iostream>
#include <stdexcept>

namespace Mice {

    Serving::Serving(Container container) : _container{container} { }
    Serving::Serving(std::istream& ist) {
        // The header must have been stripped from the incoming stream at this point
        std::string header1, header2;
        while (true) {
            std::getline(ist, header1); // header
            std::getline(ist, header2);
            if (header1 != "#") throw std::runtime_error("missing # during input");
            if (header2 == "END SERVING") break;  // footer
            else if (header2 == "CONTAINER") _container = Mice::Container{ist};
            else if (header2 == "SCOOP") _scoops.push_back(Mice::Scoop{ist});
            else if (header2 == "TOPPING") _toppings.push_back(Mice::Topping{ist});
            else throw std::runtime_error("invalid item type in Serving");
        }
    }
    
    void Serving::save(std::ostream& ost) {
        ost << "#" << std::endl << "SERVING" << std::endl; // header
        _container.save(ost);
        for (Scoop& s : _scoops) s.save(ost);
        for (Topping& t : _toppings) t.save(ost);
        ost << "#" << std::endl << "END SERVING" << std::endl; // footer
    }
    
    Container Serving::container() const {return _container;}
    
    std::vector<Scoop> Serving::scoops() const {return _scoops;}
    std::vector<Topping> Serving::toppings() const {return _toppings;}
    
    void Serving::add_scoop(Scoop scoop) {_scoops.push_back(scoop);}
    void Serving::add_topping(Topping topping) {_toppings.push_back(topping);}
    
    double Serving::cost() const {
        double total = _container.cost();
        for (Scoop scoop : _scoops) total += scoop.cost();
        for (Topping topping : _toppings) total += topping.cost();
        return total;
    }
    
    double Serving::price() const {
        double total = _container.price();
        for (Scoop scoop : _scoops) total += scoop.price();
        for (Topping topping : _toppings) total += topping.price();
        return total;
    }
    
    std::string Serving::show_server() const { 
        std::string result = _container.show_server() + '\n';
        for (auto s : _scoops) result += s.show_server() + '\n';
        for (auto t : _toppings) result += t.show_server() + '\n';
        return result;
    }
    
}
    
// OPERATOR OVERLOADING for class Serving
std::ostream& operator<<(std::ostream& os, const Mice::Serving& serving) {
    os << serving.container();
    for (Mice::Scoop s : serving.scoops()) os << std::endl << s;
    for (Mice::Topping t : serving.toppings()) os << std::endl << t;
    return os;
}
    
