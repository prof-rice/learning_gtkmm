#include "java.h"

Java::Java(std::string name, double price, double cost, Darkness darkness)
    : Product{name, price, cost}, _darkness{darkness} { }

void Java::add_shot(Shot shot) {_shots.push_back(shot);}

Java::Java(std::istream& ist) : Product{ist} {
    int i;
    ist >> i; ist.ignore(); _darkness = static_cast<Darkness>(i);
    int num_shots;
    ist >> num_shots; ist.ignore();
    for(int shot=0; shot<num_shots; ++shot) {ist >> i; ist.ignore(); _shots.push_back(static_cast<Shot>(i));}
}
    
void Java::save(std::ostream& ost) {
    Product::save(ost);
    ost << static_cast<int>(_darkness) << std::endl;
    ost << _shots.size() << std::endl;
    for (Shot& s : _shots) ost << static_cast<int>(s) << std::endl;
}
std::string Java::type() {return "Java";}
std::string Java::to_string() {
    std::string result =  Product::to_string() + " (" + darkness_to_string[_darkness]
        + ")";
    std::string separator = " with ";
    for (auto s : _shots) {result += separator + shot_to_string[s]; separator = ", ";}
    return result;
}
