#include "product_order.h"
#include <iostream>
#include <sstream>

const std::string classname = "Product_order";
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
        Product_order p{"Sandwich", 3.50, 1};
        verify("Sandwich", p.name(), "Invalid name");
        verify(3.50, p.price(), "Invalid price");
        verify(1, p.quantity(), "Invalid quantity");
    } catch(std::exception e) {
        std::cerr << "FAIL: " << classname << " exception during test vector " << test_vector << ": " << e.what() << std::endl;
        result_code |= test_vector;
    }

    // Test empty string and zero price
    try {
        Product_order p{"", 0, 0};
        verify("", p.name(), "Invalid name");
        verify(0, p.price(), "Invalid price");
        verify(0, p.quantity(), "Invalid quantity");
    } catch(std::exception e) {
        std::cerr << "FAIL: " << classname << " exception during test vector " << test_vector << ": " << e.what() << std::endl;
        result_code |= test_vector;
    }

    // Test operator<<
    try {
        std::ostringstream oss;
        Product_order p{"Pizza", 4.83, 2};
        oss << p;
        verify("Pizza (2 @ $4.83 = $9.66)", oss.str(), "Operator<<");
    } catch(std::exception e) {
        std::cerr << "FAIL: " << classname << " exception during test vector " << test_vector << ": " << e.what() << std::endl;
        result_code |= test_vector;
    }
    return result_code;
}

