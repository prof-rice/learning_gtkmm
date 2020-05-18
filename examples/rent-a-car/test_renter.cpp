#include "renter.h"
#include <iostream>
#include <sstream>

int main() {
    bool pass = true;

    {
      // Test default constructor
      Renter renter;
      std::string expected = ", , ";
      if (renter.to_string() != expected) {
          std::cerr << "FAIL: Renter construction failed" << std::endl;
          std::cerr << "  Expected: '" << expected  << "'" << std::endl;
          std::cerr << "  Actual:   '" << renter.to_string() << "'" << std::endl;
          pass = false;
      }
    }

    {
      // Test 3-string constructor
      Renter renter{"Prof Rice", "12345678", "817-555-1212"};
      std::string expected = "Prof Rice, 12345678, 817-555-1212";
      if (renter.to_string() != expected) {
          std::cerr << "FAIL: Renter construction failed" << std::endl;
          std::cerr << "  Expected: '" << expected  << "'" << std::endl;
          std::cerr << "  Actual:   '" << renter.to_string() << "'" << std::endl;
          pass = false;
      }
    }

    {
      // Test operator<< overload
      Renter renter{"Jessica Fletcher", "1286416", "207-256-1024"};
      std::string expected = "Jessica Fletcher, 1286416, 207-256-1024";
      std::ostringstream ost;
      ost << renter;
      if (ost.str() != expected) {
          std::cerr << "FAIL: Renter construction failed" << std::endl;
          std::cerr << "  Expected: '" << expected  << "'" << std::endl;
          std::cerr << "  Actual:   '" << renter.to_string() << "'" << std::endl;
          pass = false;
      }
    }

    if (!pass) return -1;
    return 0;
}

