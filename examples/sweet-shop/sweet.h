#ifndef __SWEET_H
#define __SWEET_H

#include <string>
#include <ostream>

class Sweet {
  public:
    Sweet(std::string name, double price);
    std::string name() const;
    double price() const;
  private:
    std::string _name;
    double _price;
};
std::ostream& operator<<(std::ostream& ost, const Sweet& sweet);
#endif
