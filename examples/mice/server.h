#ifndef _SERVER_H
#define _SERVER_H
#include "person.h"
#include <string>
#include <iostream>
#include <fstream>

namespace Mice {
    class Server : public Person {
      public:
        Server(std::string name, std::string id, std::string phone, double salary=8.0);
        Server(std::istream& ist);
        void save(std::ostream& ost);

        bool fill_order_and_pay();     // True if server was paid for this order
        bool restock_and_pay();        // True if server was paid for this restock
        double pay_server();           // Returns server's salary for this paycheck
        int num_orders();              // Returns number of orders filled by this server
        int salary();                  // Returns salary of this server per hour
        static const int PAY_PERIOD = 10; // Number of orders between paychecks
        static const int RESTOCK_PAY = 2; // Equivalent number of orders per restock
      private:
        int _num_orders;
        double _salary;
    };
}

#endif
