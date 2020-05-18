#include "server.h"
#include "test_server.h"
#include "test_people.h"
#include <iostream>
#include <sstream>

bool test_server() {

  // Test constructor and is_active using TEMPLATE

  return test_people<Mice::Server>("Server");

}
