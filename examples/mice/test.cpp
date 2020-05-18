#include "test_item.h"
#include "test_container.h"
#include "test_scoop.h"
#include "test_topping.h"
#include "test_person.h"
#include "test_server.h"
#include "test_customer.h"
#include <iostream>

int main() {
  if (!(test_item() &&
        test_container() &&
        test_scoop() &&
        test_topping() &&
        test_person() &&
        test_server() &&
        test_customer() 
     ))
    std::cerr << "fail" << std::endl;
} 
