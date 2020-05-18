#include "person.h"

namespace Mice {
Person::Person(std::string name, std::string id, std::string phone)
             : _name{name}, _id{id}, _phone{phone}, _active{true} { }
Person::Person() : _name{""}, _id{""}, _phone{""}, _active{true} { }
std::string Person::name() {return _name;}
std::string Person::id() {return _id;}
std::string Person::phone() {return _phone;}
bool Person::is_active() {return _active;}
void Person::set_active(bool active) {_active = active;}
}
