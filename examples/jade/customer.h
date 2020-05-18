#ifndef __CUSTOMER_H
#define __CUSTOMER_H
#include <string>
#include <ostream>
#include <istream>
#include <vector>

class Customer {
  public:
    Customer(std::string renter, std::string renter_phone);
    Customer();
    Customer(std::istream& ist);
    void save(std::ostream& ost);
    std::string to_string() const;
    friend std::ostream& operator<<(std::ostream& ost, const Customer& customer);
  private:
    std::string _customer;
    std::string _customer_phone;  
};
#endif
