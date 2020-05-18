#include <typeinfo>
#include <iostream>

class Base {
  public:
    virtual std::string my_name() {return typeid(*this).name();}
};

class Derived : public Base { };

int main() {
  Base b;
  Derived d;

  std::cout << "Base is " << b.my_name() << ", and Derived is " << d.my_name() << std::endl;
}
