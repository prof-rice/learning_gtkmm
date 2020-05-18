#include "vehicle.h"
#include <stdexcept>

Vehicle::Vehicle(int year, std::string make, std::string model, Body_style body_style)
    : _year{year}, _make{make}, _model{model}, _body_style{body_style}, _is_rented{false} { }

Vehicle::Vehicle(std::istream& ist) {
    int temp;
    ist >> _year; ist.ignore();
    std::getline(ist, _make);
    std::getline(ist, _model);
    ist >> temp; ist.ignore();
    _body_style = (Body_style)temp;
    ist >> temp; ist.ignore();
    _is_rented = (temp != 0);
    _renter = Renter{ist};  
}
void Vehicle::save(std::ostream& ost) {
    ost << _year << std::endl;
    ost << _make << std::endl;
    ost << _model << std::endl;
    ost << (int)_body_style << std::endl;
    ost << (int)_is_rented << std::endl;
    _renter.save(ost);
}

void Vehicle::rent_vehicle(Renter renter) {
    if (_is_rented) throw std::runtime_error{"Attempt to rent a rented vehicle"};
    _is_rented = true;
    _renter = renter;
}
void Vehicle::return_vehicle() {
    if (!_is_rented) throw std::runtime_error{"Attempt to return an unrented vehicle"};
    _is_rented = false;
}

std::vector<std::string> Vehicle::to_strings() {
    std::vector<std::string> result;
    result.push_back(std::to_string(_year));
    result.push_back(_make);
    result.push_back(_model);
    result.push_back(body_style_to_string());
    if (_is_rented) {
        std::vector<std::string> renter = _renter.to_strings();
        result.push_back(renter[0]);
        result.push_back(renter[1]);
        result.push_back(renter[2]);
    } else {
        result.push_back("");
        result.push_back("");
        result.push_back("");
    }
    return result;
}
std::string Vehicle::make() const {return _make;}
std::string Vehicle::model() const {return _model;}
int Vehicle::year() const {return _year;}
Body_style Vehicle::body_style() const {return _body_style;}
bool Vehicle::is_rented() {return _is_rented;}
std::string Vehicle::body_style_to_string() const {
    if (body_style() == Body_style::SEDAN) return "Sedan"; 
    else if (body_style() == Body_style::HATCHBACK) return "Hatchback";
    else if (body_style() == Body_style::MINIVAN) return "Minivan";
    else if (body_style() == Body_style::TRUCK) return "Truck";
    else if (body_style() == Body_style::CROSSOVER) return "Crossover";
    else return "SUV";
}
std::string Vehicle::to_string() const {
    std::string result = std::to_string(year()) + ' ' + make() + ' ' + model() + ' ' + body_style_to_string();
    if (_is_rented)
        result += " (rented to " + _renter.to_string() + ")";
    return result;
}

std::ostream& operator<<(std::ostream& ost, const Vehicle& vehicle) {
    ost << vehicle.to_string();
    return ost;
}

 
