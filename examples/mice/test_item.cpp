#include "test_item.h"
#include "item.h"
#include <iostream>
#include <sstream>

bool test_item() {
  std::string expected = "";
  bool passed = true; // Optimist!

  //
  // Test constructor
  //

  std::string x_name = "Fudge Ripple";
  std::string x_description = "Chocolatey goodness in vanilla swirl";
  double x_cost = 0.75;
  double x_price = 1.50;

  Mice::Item item{x_name, x_description, x_cost, x_price};

  std::ostringstream os;
  os << item;

  if (os.str() != "                      Item: Fudge Ripple $1.50") {
    std::cerr << "#### Item operator<< fail" << std::endl;
    std::cerr << "Expected:                       Item: Fudge Ripple $1.50" << std::endl;
    std::cerr << "Actual:   " << os.str() << std::endl;
  }


  if (item.name() != x_name ||
      item.description() != x_description ||
      item.cost() != x_cost ||
      item.price() != x_price ||
      item.quantity() != 0 ||
      item.type() != "Item") {
    std::cerr << "#### Item constructor fail" << std::endl;
    std::cerr << "Expected: " << x_name << ',' 
                              << x_description << ','
                              << x_cost << ','
                              << x_price << ','
                              << '0' << ','
                              << "Item" << std::endl;
    std::cerr << "Actual:   " << item.name() << ',' 
                              << item.description() << ','
                              << item.cost() << ','
                              << item.price() << ','
                              << item.quantity() << ','
                              << item.type() << std::endl;
  }

  //
  // Test restock
  //
  item.restock();
  if (item.quantity() != 25) {
    std::cerr << "#### Item: Restock failed" << std::endl;
    std::cerr << "Expected: 25  Actual: " << item.quantity() << std::endl;
    passed = false;
  }

  item.restock(50);
  if (item.quantity() != 50) {
    std::cerr << "#### Item: Restock failed" << std::endl;
    std::cerr << "Expected: 50  Actual: " << item.quantity() << std::endl;
    passed = false;
  }

  //
  // Test consume
  //
  item.consume();
  if (item.quantity() != 49) {
    std::cerr << "#### Item: Consume failed" << std::endl;
    std::cerr << "Expected: 49  Actual: " << item.quantity() << std::endl;
    passed = false;
  }

  item.consume(3);
  if (item.quantity() != 46) {
    std::cerr << "#### Item: Consume failed" << std::endl;
    std::cerr << "Expected: 46  Actual: " << item.quantity() << std::endl;
    passed = false;
  }

  item.consume(46);
  if (item.name() != x_name ||
      item.description() != x_description ||
      item.cost() != x_cost ||
      item.price() != x_price ||
      item.quantity() != 0 ||
      item.type() != "Item") {
    std::cerr << "#### Item: restock or consume fail" << std::endl;
    std::cerr << "Expected: " << x_name << ',' 
                              << x_description << ','
                              << x_cost << ','
                              << x_price << ','
                              << '0' << ','
                              << "Item" << std::endl;
    std::cerr << "Actual:   " << item.name() << ',' 
                              << item.description() << ','
                              << item.cost() << ','
                              << item.price() << ','
                              << item.quantity() << ','
                              << item.type() << std::endl;
    passed = false;
  }
  //
  // Report results
  //

  return passed;
}
