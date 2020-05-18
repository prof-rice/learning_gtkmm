#include "test_container.h"
#include "container.h"
#include <iostream>
#include <sstream>

bool test_container() {
  std::string expected = "";
  bool passed = true; // Optimist!

  //
  // Test constructor
  //

  std::string x_name = "Waffle Cone";
  std::string x_description = "A dry, cone-shaped pastry with a waffle texture";
  double x_cost = 0.30;
  double x_price = 0.99;
  int x_max_scoops = 3;

  Mice::Container container{x_name, x_description, x_cost, x_price, x_max_scoops};

  std::ostringstream os;
  os << container;

  if (os.str() != "                  Container: Waffle Cone $0.99") {
    std::cerr << "#### Container operator<< fail" << std::endl;
    std::cerr << "Expected:                   Container: Waffle Cone $0.99" << std::endl;
    std::cerr << "Actual:   " << os.str() << std::endl;
  }

  if (container.name() != x_name ||
      container.description() != x_description ||
      container.cost() != x_cost ||
      container.price() != x_price ||
      container.type() != "Container" ||
      container.max_scoops() != x_max_scoops) {
    std::cerr << "#### Container constructor fail" << std::endl;
    std::cerr << "Expected: " << x_name << ','
                              << x_description << ','
                              << x_cost << ','
                              << x_price << ','
                              << "Container" << ','
                              << x_max_scoops << std::endl;
    std::cerr << "Actual:   " << container.name() << ','
                              << container.description() << ','
                              << container.cost() << ','
                              << container.price() << ','
                              << container.type() << ','
                              << container.max_scoops() << std::endl;
    passed = false;
  }

  // Test I/O
  std::ostringstream ost;
  container.save(ost);

  std::istringstream ist{ost.str()};
  std::string header1, header2;
  getline(ist, header1);
  getline(ist, header2);
  if (header1 != "#" && header2 != "CONTAINER") {
      std::cerr << "#### Container I/O fail" << std::endl;
      std::cerr << "Expected header: '#' and 'CONTAINER'" << std::endl;
      std::cerr << "Actual header: '" << header1 << "' and '" << header2 << "'" << std::endl;
  }

  Mice::Container clone{ist};

  if (container.name() != clone.name() ||
    container.description() != clone.description() ||
    container.cost() != clone.cost() ||
    container.price() != clone.price() ||
    container.type() != clone.type() ||
    container.max_scoops() != clone.max_scoops()) {
      std::cerr << "#### Container I/O fail" << std::endl;
      std::cerr << "Expected:   " << container.name() << ','
                                << container.description() << ','
                                << container.cost() << ','
                                << container.price() << ','
                                << container.type() << ','
                                << container.max_scoops() << std::endl;
      std::cerr << "Actual: " << clone.name() << ','
                              << clone.description() << ','
                              << clone.cost() << ','
                              << clone.price() << ','
                              << clone.type() << ','
                              << clone.max_scoops() << std::endl;
      passed = false;
  }

  //
  // Report results
  //

  return passed;
}
