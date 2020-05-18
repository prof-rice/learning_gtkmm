#include "test_scoop.h"
#include "scoop.h"
#include <iostream>
#include <sstream>

bool test_scoop() {
  std::string expected = "";
  bool passed = true; // Optimist!

  //
  // Test constructor
  //

  std::string x_name = "Fudge Ripple";
  std::string x_description = "Chocolatey goodness in vanilla swirl";
  double x_cost = 0.75;
  double x_price = 1.50;

  Mice::Scoop scoop{x_name, x_description, x_cost, x_price};

  std::ostringstream os;
  os << scoop;

  if (os.str() != "                     Scoop: Fudge Ripple $1.50") {
    std::cerr << "#### Scoop operator<< fail" << std::endl;
    std::cerr << "Expected:                      Scoop: Fudge Ripple $1.50" << std::endl;
    std::cerr << "Actual:   " << os.str() << std::endl;
  }

  if (scoop.name() != x_name ||
      scoop.description() != x_description ||
      scoop.cost() != x_cost ||
      scoop.price() != x_price ||
      scoop.type() != "Scoop" ||
      scoop.quantity() != 0) {
    std::cerr << "#### Scoop constructor fail" << std::endl;
    std::cerr << "Expected: " << x_name << ','
                              << x_description << ','
                              << x_cost << ','
                              << x_price << ','
                              << "Scoop" << ','
                              << '0' << std::endl;
    std::cerr << "Actual:   " << scoop.name() << ','
                              << scoop.description() << ','
                              << scoop.cost() << ','
                              << scoop.price() << ','
                              << scoop.type() << ','
                              << scoop.quantity() << std::endl;
    passed = false;
  }

  // Test I/O
  std::ostringstream ost;
  scoop.save(ost);

  std::istringstream ist{ost.str()};
  std::string header1, header2;
  getline(ist, header1);
  getline(ist, header2);
  if (header1 != "#" && header2 != "SCOOP") {
      std::cerr << "#### Scoop I/O fail" << std::endl;
      std::cerr << "Expected header: '#' and 'SCOOP'" << std::endl;
      std::cerr << "Actual header: '" << header1 << "' and '" << header2 << "'" << std::endl;
  }

  Mice::Scoop clone{ist};

  if (scoop.name() != clone.name() ||
      scoop.description() != clone.description() ||
      scoop.cost() != clone.cost() ||
      scoop.price() != clone.price() ||
      scoop.type() != clone.type() ||
      scoop.quantity() != clone.quantity()) {
    std::cerr << "#### Scoop constructor fail" << std::endl;
    std::cerr << "Expected:   " << scoop.name() << ','
                              << scoop.description() << ','
                              << scoop.cost() << ','
                              << scoop.price() << ','
                              << scoop.type() << ','
                              << scoop.quantity() << std::endl;
    std::cerr << "Actual: " << clone.name() << ','
                              << clone.description() << ','
                              << clone.cost() << ','
                              << clone.price() << ','
                              << clone.type() << ','
                              << clone.quantity() << std::endl;
    passed = false;
  }

  //
  // Report results
  //

  return passed;
}
