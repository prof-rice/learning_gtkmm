#include "product.h"
#include <iostream>
#include <sstream>

const std::string classname = "Product";
int result_code = 0;
int test_vector = 1;

void verify(std::string expected, std::string actual, std::string msg) {
    if(actual != expected) {
        std::cerr << "FAIL: Class " << classname << " (code " << test_vector << "):  " << msg << '\n'
                  << "  Expected: |" << expected << "|\n"
                  << "  Actual:   |" << actual   << "|\n";
        result_code |= test_vector;
    }
    test_vector <<= 1;
} 

void verify(double expected, double actual, std::string msg) {
    if(actual != expected) {
        std::cerr << "FAIL: Class " << classname << " (code " << test_vector << "):  " << msg << '\n'
                  << "  Expected: " << expected << '\n'
                  << "  Actual:   " << actual << std::endl;
        result_code |= test_vector;
    }
    test_vector <<= 1;
} 

int main() {

    // Test the normative case 
    try {
        Product p{"Sandwich", 3.50};
        verify("Sandwich", p.name(), "Invalid name");
        verify(3.50, p.price(), "Invalid price");
    } catch(std::exception e) {
        std::cerr << "FAIL: Exception during test vector " << test_vector << ": " << e.what() << std::endl;
    }

    // Test empty string and zero price
    try {
        Product p{"", 0};
        verify("", p.name(), "Invalid name");
        verify(0, p.price(), "Invalid price");
    } catch(std::exception e) {
        std::cerr << "FAIL: Exception during test vector " << test_vector << ": " << e.what() << std::endl;
        result_code |= test_vector;
    }

    // Test operator<<
    try {
        std::ostringstream oss;
        Product p{"Coffee", 2.15};
        oss << p;
        verify("Coffee ($2.15)", oss.str(), "Operator<<");
    } catch(std::exception e) {
        std::cerr << "FAIL: Exception during test vector " << test_vector << ": " << e.what() << std::endl;
        result_code |= test_vector;
    }
    return result_code;
}

