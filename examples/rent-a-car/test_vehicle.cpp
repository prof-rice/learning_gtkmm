#include "vehicle.h"
#include <iostream>
#include <sstream>

int main() {
    bool pass = true;

    {
      // Test constructor
      Vehicle vehicle{2002, "Ford", "Mustang", Body_style::SEDAN};
      if ( vehicle.year() != 2002       || vehicle.make() != "Ford"
        || vehicle.model() != "Mustang" || vehicle.body_style() != Body_style::SEDAN) {
          std::cerr << "FAIL: Vehicle construction failed" << std::endl;
          pass = false;
      }
    }

    {
      // Test operator<< overload
      Vehicle vehicle{1918, "Chevy", "Four-Ninty", Body_style::TRUCK};
      std::ostringstream ost;
      ost << vehicle;
      const std::string expected = "1918 Chevy Four-Ninty Truck";
      if (ost.str() != expected) {
          std::cerr << "FAIL: Vehicle output stream failed" << std::endl;
          std::cerr << "  Expected: '" << expected  << "'" << std::endl;
          std::cerr << "  Actual:   '" << ost.str() << "'" << std::endl;
          pass = false;
      }
    }

    {
      // Test rent vehicle
      Vehicle vehicle{2014, "Hennessey", "Venom F5", Body_style::SEDAN};
      Renter renter{"Prof Rice", "314159265", "817-272-3785"};
      vehicle.rent_vehicle(renter);
      std::ostringstream ost;
      ost << vehicle;
      std::string expected = "2014 Hennessey Venom F5 Sedan (rented to Prof Rice, 314159265, 817-272-3785)";
      if (ost.str() != expected) {
          std::cerr << "FAIL: Vehicle rental failed" << std::endl;
          std::cerr << "  Expected: '" << expected  << "'" << std::endl;
          std::cerr << "  Actual:   '" << ost.str() << "'" << std::endl;
          pass = false;
      }

      // Test rent vehicle that's already rented
      try {
          Renter renter{"Prof Quirrel", "12345678", "817-555-1212"};
          vehicle.rent_vehicle(renter);
          std::cerr << "FAIL: Vehicle rented twice!" << std::endl;
          pass = false;
      } catch(std::runtime_error e) {
      }

      // Test return vehicle
      vehicle.return_vehicle();
      std::ostringstream ostr;
      ostr << vehicle;
      expected = "2014 Hennessey Venom F5 Sedan";
      if (ostr.str() != expected) {
          std::cerr << "FAIL: Vehicle rental return failed" << std::endl;
          std::cerr << "  Expected: '" << expected  << "'" << std::endl;
          std::cerr << "  Actual:   '" << ostr.str() << "'" << std::endl;
          pass = false;
      }

      // Test return vehicle that's not rented
      try {
          vehicle.return_vehicle();
          std::cerr << "FAIL: Vehicle returned twice!" << std::endl;
          pass = false;
      } catch(std::runtime_error e) {
      }
    }

    if (!pass) return -1;
    return 0;
}

