#include "test_topping.h"
#include "topping.h"
#include <iostream>
#include <sstream>

bool test_topping() {
  std::string expected = "";
  bool passed = true; // Optimist!

  //
  // Test constructor
  //

  std::string x_name = "Maraschino Cherry";
  std::string x_description = "A sweet, plump cherry preserved in maraschino syrup";
  double x_cost = 0.10;
  double x_price = 0.50;
  int x_amount = Mice::Topping::EXTRA_AMOUNT;

  Mice::Topping topping{x_name, x_description, x_cost, x_price, x_amount};

  std::ostringstream os;
  os << topping;

  if (os.str() != "              Topping: Maraschino Cherry $0.50") {
    std::cerr << "#### Topping operator<< fail" << std::endl;
    std::cerr << "Expected:               Topping: Maraschino Cherry $0.50" << std::endl;
    std::cerr << "Actual:   " << os.str() << std::endl;
  }

  if (topping.name() != x_name ||
      topping.description() != x_description ||
      topping.cost() != x_cost ||
      topping.price() != x_price ||
      topping.type() != "Topping" ||
      topping.amount() != Mice::Topping::EXTRA_AMOUNT) {
    std::cerr << "#### Topping constructor fail" << std::endl;
    std::cerr << "Expected: " << x_name << ','
                              << x_description << ','
                              << x_cost << ','
                              << x_price << ','
                              << "Topping" << ','
                              << x_amount << std::endl;
    std::cerr << "Actual:   " << topping.name() << ','
                              << topping.description() << ','
                              << topping.cost() << ','
                              << topping.price() << ','
                              << topping.type() << ','
                              << topping.amount() << std::endl;
    passed = false;
  }

  // Test I/O
  std::ostringstream ost;
  topping.save(ost);

  std::istringstream ist{ost.str()};
  std::string header1, header2;
  getline(ist, header1);
  getline(ist, header2);
  if (header1 != "#" && header2 != "TOPPING") {
      std::cerr << "#### Container I/O fail" << std::endl;
      std::cerr << "Expected header: '#' and 'TOPPING'" << std::endl;
      std::cerr << "Actual header: '" << header1 << "' and '" << header2 << "'" << std::endl;
  }

  Mice::Topping clone{ist};

  if (topping.name() != clone.name() ||
      topping.description() != clone.description() ||
      topping.cost() != clone.cost() ||
      topping.price() != clone.price() ||
      topping.type() != clone.type() ||
      topping.amount() != clone.amount()) {
    std::cerr << "#### Topping constructor fail" << std::endl;
    std::cerr << "Expected: " << topping.name() << ','
                              << topping.description() << ','
                              << topping.cost() << ','
                              << topping.price() << ','
                              << topping.type() << ','
                              << topping.amount() << std::endl;
    std::cerr << "Actual:   " << clone.name() << ','
                              << clone.description() << ','
                              << clone.cost() << ','
                              << clone.price() << ','
                              << clone.type() << ','
                              << clone.amount() << std::endl;
    passed = false;
  }

  //
  // Report results
  //

  return passed;
}
