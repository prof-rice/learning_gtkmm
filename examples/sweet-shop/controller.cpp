#include "controller.h"

Controller::Controller(Store& store) : _store{store}, _view{*(new View{store})} { }
Controller::Controller() : Controller{*(new Store{})} { }

// ///////////////////////////////////////////////////////////////////
// Command line interface
// ///////////////////////////////////////////////////////////////////

int Controller::cli() {
    char cmd = ' ';
    _view.splash();
    while(cmd != 'X') {
        _view.main_menu();
        cmd = toupper(get_char("Command? "));
        _view.splash();
        if(std::cin) {
            switch (cmd) {
                case 'M': list_sweets(); break;
                case 'O': place_order(); break;
                case 'L': list_order(); break;
                case 'S': add_sweet(); break;
                case 'X': std::cout << "Thanks for using MUSS!\n\n"; break;
                default: std::cerr << "### Invalid command\n";
            }
        } else {
            std::cerr << '\n';
            exit(0);
        }
    }   
}

// ///////////////////////////////////////////////////////////////////
// Commands
// ///////////////////////////////////////////////////////////////////

void Controller::add_sweet() {
    std::cout << "Adding a new sweet to the store\n\n";

    std::string name;
    double price;
    std::cout << "Enter name of new sweet: ";
    std::getline(std::cin, name);
    if(name.size()) {
        price = get_double("Enter price for " + name + ": ", 0.0);
        if(price > 0.0) {
            Sweet sweet{name, price};
            std::cout << "### Adding " << sweet << std::endl;
            _store.add(sweet);
        }
    }
}

void Controller::list_sweets() {
    _view.menu();
}

void Controller::place_order() {
    if (_store.num_sweets() < 1) {
        std::cerr << "### No sweets have been added yet" << std::endl;
        return;
    }

    std::cout << "Placing a new order\n\n";

    Order order;
    int quantity;
    int sweet = 0;
    do {
        std::cout << order << '\n';
        _view.menu();
        sweet = get_int("\nSweet to order: ", 0, _store.num_sweets());
        quantity = get_int("Quantity: ", 0);
        if (quantity > 0) {
            order.add(quantity, _store.sweet(sweet));
        }
    } while (toupper(get_char("Add another sweet (y/n)? ")) != 'N');
    if (order.size() > 0) {
        std::cout << "Placing order:\n" << order << std::endl;
        _store.add(order);
    }
}        

void Controller::list_order() {
    std::cout << "Listing an existing order\n\n";

    int order;
    if (_store.num_orders()) {
        order = get_int("Enter order number(0 to " + std::to_string(_store.num_orders()-1) + "): ", 0, _store.num_orders()-1);
        std::cout << "\n Order #" << order << " ($" << _store.order(order).price() << ")\n" << _store.order(order) << std::endl;
    } else {
        std::cerr << "### No orders have been placed yet" << std::endl;
    }
}
// ///////////////////////////////////////////////////////////////////
// Utilities
// ///////////////////////////////////////////////////////////////////

char Controller::get_char(std::string prompt, char min, char max) {
  char c;
  std::string s;
  while(true) {
    std::cout << prompt;

    // Successfully entered a char
    if(std::cin >> c) {
        std::cin.ignore(65535, '\n');
        if (min <= c && c <= max) return c;

        // Char was out of range
        std::cerr << "### Must be between " << min << " and " << max << ".\n";
        continue;
    }

    // End of file - no more input possible
    if (std::cin.eof()) exit(0);

    // Invalid input - clear the error and buffer and display error message
    std::cin.clear();
    std::cin.ignore(65535, '\n');
    std::cerr << "### That was not a char.\n";
  }
}



int Controller::get_int(std::string prompt, int min, int max) {
  int i;
  std::string s;
  while(true) {
    std::cout << prompt;

    // Successfully entered an integer
    if(std::cin >> i) {
        std::cin.ignore(65535, '\n');
        if (min <= i && i <= max) return i;

        // Integer was out of range
        std::cerr << "### Must be between " << min << " and " << max << ".\n";
        continue;
    }

    // End of file - no more input possible
    if (std::cin.eof()) exit(0);

    // Invalid input - clear the error and buffer and display error message
    std::cin.clear();
    std::cin.ignore(65535, '\n');
    std::cerr << "### That was not an integer.\n";
  }
}

double Controller::get_double(std::string prompt, double min, double max) {
  double d;
  std::string s;
  while(true) {
    std::cout << prompt;

    // Successfully entered an double
    if(std::cin >> d) {
        std::cin.ignore(65535, '\n');
        if (min <= d && d <= max) return d;

        // Double was out of range
        std::cerr << "### Must be between " << min << " and " << max << ".\n";
        continue;
    }

    // End of file - no more input possible
    if (std::cin.eof()) exit(0);

    // Invalid input - clear the error and buffer and display error message
    std::cin.clear();
    std::cin.ignore(65535, '\n');
    std::cerr << "### That was not a double.\n";
  }
}

