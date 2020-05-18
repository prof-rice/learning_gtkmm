#include "test_customer.h"
#include "customer.h"
#include "test_people.h"
#include <iostream>
#include <sstream>

bool test_customer() {

  // Test constructor and is_active using TEMPLATE

  bool passed = test_people<Mice::Customer>("Customer");

  // Test I/O


  std::string x_name = "Charlie Chaplin";
  std::string x_id = "tramp";
  std::string x_phone = "555-1212";
  Mice::Customer customer{x_name, x_id, x_phone};

  std::ostringstream ost;
  customer.save(ost);

  std::istringstream ist{ost.str()};
  std::string header1, header2;
  getline(ist, header1);
  getline(ist, header2);
  if (header1 != "#" && header2 != "CUSTOMER") {
      std::cerr << "#### Customer I/O fail" << std::endl;
      std::cerr << "Expected header: '#' and 'CUSTOMER'" << std::endl;
      std::cerr << "Actual header: '" << header1 << "' and '" << header2 << "'" << std::endl;
  }

  Mice::Customer clone{ist};

  if (customer.name() != clone.name() ||
      customer.id() != clone.id() ||
      customer.phone() != clone.phone() ||
      customer.is_active() != clone.is_active()) {
    std::cerr << "#### Customer constructor fail" << std::endl;
    std::cerr << "Expected: " << customer.name() << ','
                              << customer.id() << ','
                              << customer.phone() << ','
                              << (customer.is_active() ? "is active" : "is not active") << std::endl;
    std::cerr << "Actual:   " << clone.name() << ','
                              << clone.id() << ','
                              << clone.phone() << ','
                              << (clone.is_active() ? "is active" : "is not active") << std::endl;
    passed = false;
  }

  return passed;
}
