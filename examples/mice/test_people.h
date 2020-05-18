#include <iostream>

// TEMPLATE for testing people classes (Person, Manager, Customer, Server, etc.)
// Some additional testing may be required for some classes

template<class T>
bool test_people(std::string class_type) {
  std::string expected = "";
  bool passed = true; // Optimist!

  //
  // Test constructor
  //

  std::string x_name = "Charlie Chaplin";
  std::string x_id = "tramp";
  std::string x_phone = "555-1212";

  T person{x_name, x_id, x_phone};

  if (person.name() != x_name ||
      person.id() != x_id ||
      person.phone() != x_phone ||
     !person.is_active()) {
    std::cerr << "#### " << class_type << " constructor fail" << std::endl;
    std::cerr << "Expected: " << x_name << ',' 
                              << x_id << ','
                              << x_phone << ','
                              << "is active" << std::endl;
    std::cerr << "Actual:   " << person.name() << ',' 
                              << person.id() << ','
                              << person.phone() << ','
                              << (person.is_active() ? "is active" : "is not active") << std::endl;
    passed = false;
  }

  //
  // Test set_active and is_active
  //

  person.set_active(false);
  if (person.is_active()) {
    std::cerr << "#### " << class_type << ": setting inactive failed" << std::endl;
    std::cerr << "Expected: is not active  Actual: " 
              << (person.is_active() ? "is active" : "is not active") << std::endl;
    passed = false;
  }

  person.set_active(true);
  if (!person.is_active()) {
    std::cerr << "#### " << class_type << ": setting active failed" << std::endl;
    std::cerr << "Expected: is active  Actual: " 
              << (person.is_active() ? "is active" : "is not active") << std::endl;
    passed = false;
  }

  return passed;
}
