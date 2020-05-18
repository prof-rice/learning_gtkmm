#include "test_person.h"
#include "person.h"
#include "test_people.h"
#include <iostream>

bool test_person() {

  // Test constructor and is_active using TEMPLATE

  return test_people<Mice::Person>("Person");

}
