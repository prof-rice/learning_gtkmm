#include "order.h"
#include <iostream>
#include <sstream>

const std::string classname = "Order";
int result_code = 0;
int test_vector = 1;

void verify(std::string expected, std::string actual, std::string msg) {
    if(actual != expected) {
        std::cerr << "FAIL: Class " << classname << " (code " << test_vector << "):  " << msg << '\n'
                  << "  Expected: |" << expected << "|\n"
                  << "  Actual:   |" << actual << "|\n";
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

void verify(Product_order expected, Product_order actual, std::string msg) {
    if(actual != expected) {
        std::cerr << "FAIL: Class " << classname << " (code " << test_vector << "):  " << msg << '\n'
                  << "  Expected: |" << expected << "|\n"
                  << "  Actual:   |" << actual   << "|\n";
        result_code |= test_vector;
    }
    test_vector <<= 1;
}  

int main() {

    // Test the normative case - 
    try {
        Order o{"customer@mavmart.com"};
        verify("customer@mavmart.com", o.email(), "Invalid email");
        verify(0, o.num_product_orders(), "Invalid number of Product_orders");
        Product_order p1{"Sandwich", 3.50, 1};
        o.add_product_order(p1);
        verify(1, o.num_product_orders(), "Invalid number of Product_orders");
        verify(p1, o.product_order(0), "Invalid product_order[0]");
    } catch(std::exception e) {
        std::cerr << "FAIL: " << classname << " exception during test vector " << test_vector << ": " << e.what() << std::endl;
        result_code |= test_vector;
    }

    // Test operator<<
    try {
        std::ostringstream oss;
        Order o{"customer@mavmart.com"};
        Product_order p1{"Sandwich", 3.50, 1};
        o.add_product_order(p1);
        Product_order p2{"Chocolate Malt", 5.25, 1};
        o.add_product_order(p2);
        oss << o;
        verify("  Sandwich (1 @ $3.50 = $3.50)\n  Chocolate Malt (1 @ $5.25 = $5.25)\n", oss.str(), "Operator<<");
    } catch(std::exception e) {
        std::cerr << "FAIL: " << classname << " exception during test vector " << test_vector << ": " << e.what() << std::endl;
        result_code |= test_vector;
    }
    return result_code;
}

