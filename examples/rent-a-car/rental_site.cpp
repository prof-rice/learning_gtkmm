#include "rental_site.h"
#include <vector>
#include <sstream> 

Rental_site::Rental_site() { }
Rental_site::Rental_site(std::istream& ist) {
    int record = 0;
    std::string obj;
    while (std::getline(ist, obj)) {
        ++record;
        if (obj == "#VEHICLE") _vehicles.push_back(Vehicle{ist});
        else if (obj == "#RENTER") _renters.push_back(Renter{ist});
        else if (!obj.size()) throw std::runtime_error{"Invalid object type: " + obj + " at record " + std::to_string(record)};
    }
}
void Rental_site::save(std::ostream& ost) {
    for (auto v : _vehicles) {
        ost << "#VEHICLE" << std::endl;
        v.save(ost);
    }
    for (auto r : _renters) {
        ost << "#RENTER" << std::endl;
        r.save(ost);
    }
}

std::vector<std::vector<std::string>> Rental_site::vehicles_to_strings() {
    std::vector<std::vector<std::string>> result;
    for (auto v : _vehicles) result.push_back(v.to_strings());
    return result;
}

std::vector<std::string> Rental_site::vehicles(bool rented, bool unrented) {
    std::vector<std::string> result;
    for (auto v : _vehicles) {
        if ((v.is_rented() && rented) || (!v.is_rented() && unrented)) {
            std::ostringstream ost;
            ost << v;
            result.push_back(ost.str());
        } else {
            result.push_back("");
        }
    }
    return result;
}

std::vector<std::string> Rental_site::renters() {
    std::vector<std::string> result;
    for (auto r : _renters) {
        std::ostringstream ost;
        ost << r;
        result.push_back(ost.str());
    }
    return result;
}

void Rental_site::add_vehicle(Vehicle vehicle) {
    _vehicles.push_back(vehicle);
}

void Rental_site::add_renter(Renter renter) {
    _renters.push_back(renter);
}

void Rental_site::rent_vehicle(int vehicle, int renter) {
    _vehicles[vehicle].rent_vehicle(_renters[renter]);
}

void Rental_site::return_vehicle(int vehicle) {
    _vehicles[vehicle].return_vehicle();
}
