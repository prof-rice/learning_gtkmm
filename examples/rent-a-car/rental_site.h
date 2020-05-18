#ifndef __RENTAL_SITE_H
#define __RENTAL_SITE_H
#include "vehicle.h"
#include "renter.h"
#include <vector>

class Rental_site {
  public:
    Rental_site();
    Rental_site(std::istream& ist);
    void save(std::ostream& ost);

    std::vector<std::string> vehicles(bool rented=true, bool unrented=true);
    std::vector<std::vector<std::string>> vehicles_to_strings();
    std::vector<std::string> renters();
    void add_vehicle(Vehicle vehicle);
    void add_renter(Renter renter);
    void rent_vehicle(int vehicle, int renter);
    void return_vehicle(int vehicle);
  private:
    std::vector<Vehicle> _vehicles;
    std::vector<Renter> _renters;
};
#endif
