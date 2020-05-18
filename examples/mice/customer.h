#ifndef _CUSTOMER_H
#define _CUSTOMER_H
#include "person.h"
#include <string>
#include <iostream>
#include <fstream>

namespace Mice {
    class Customer : public Person {
      public:
        Customer(std::string name, std::string id, std::string phone);
        Customer(std::istream& ist);
        void save(std::ostream& ost);
    };
}

#endif
