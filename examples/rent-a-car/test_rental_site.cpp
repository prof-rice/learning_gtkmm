#include "rental_site.h"
#include "renter.h"
#include <iostream>
#include <sstream>

int main() {
    bool pass = true;
    Rental_site r;

    // Test adding a vehicle
    r.add_vehicle(Vehicle{2002, "Ford", "Mustang", Body_style::SEDAN});
    if (r.vehicles()[0] != "2002 Ford Mustang Sedan") {
        std::cerr << "FAIL: Rental_site::add_vehicle Mustang failed" << std::endl;
        pass = false;
    }

    r.add_vehicle(Vehicle{1918, "Chevy", "Four-Ninty", Body_style::TRUCK});
    if (r.vehicles()[1] != "1918 Chevy Four-Ninty Truck") {
        std::cerr << "FAIL: Rental_site::add_vehicle Four-Ninty failed" << std::endl;
        pass = false;
    }

    r.add_renter(Renter{"Prof Rice", "314159265", "817-272-3785"});
    r.rent_vehicle(1, 0);
    if (r.vehicles()[1] != "1918 Chevy Four-Ninty Truck (rented to Prof Rice, 314159265, 817-272-3785)") {
        std::cerr << "FAIL: Rental_site::rent_vehicle Four-Ninty failed" << std::endl;
        pass = false;
    }

    r.return_vehicle(1);
    if (r.vehicles()[1] != "1918 Chevy Four-Ninty Truck") {
        std::cerr << "FAIL: Rental_site::return_vehicle Four-Ninty failed" << std::endl;
        pass = false;
    }

    if (!pass) return -1;
    return 0;
}

