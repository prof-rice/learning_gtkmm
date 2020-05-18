#include "mainwin.h"
#include <exception>
#include <stdexcept>
#include <iostream>
#include <vector>

Mice::Serving Mainwin::create_serving() {
    int container = select_container();
    if (container == -1) throw std::runtime_error("Canceled");

    Mice::Serving serving{_emp->container(container)};

    bool has_no_scoops = true;
    for (int i=0; i<_emp->container(container).max_scoops(); ++i) {
        int scoop = select_scoop();
        if (scoop == -1) break;
        serving.add_scoop(_emp->scoop(scoop));
        has_no_scoops = false;
    }
    if (has_no_scoops) throw std::runtime_error("Canceled");

    if (_emp->num_toppings() > 0) {
        std::vector<std::string> amounts = 
            {"Light", "Normal", "Extra", "Drenched"};
        while (true) {
            int topping = select_topping();
            if (topping == -1) break;
            try {
                _emp->topping(topping).set_amount(
                    select_from_vector(amounts, "Amount")+1);
            } catch (std::exception e) {
                break;
            }
            serving.add_topping(_emp->topping(topping));
        }
    }

    return serving;
}
