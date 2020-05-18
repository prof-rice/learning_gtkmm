#include "store.h"
#include <iostream>
#include <sstream>

const std::string classname = "Store";
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

    // Test the constructor 
    try {
        Store st{"Mavmart"};
        verify("Mavmart", st.name(), "Invalid store name");

    // Test product creation 
        verify(0, st.num_products(), "Invalid number of products");
        Product p{"Sandwich", 3.50};
        st.add_product(p);
        verify(1, st.num_products(), "Invalid number of products");
        verify("Sandwich", st.product(0).name(), "Invalid name");
        verify(3.50, st.product(0).price(), "Invalid price");

    // Test order creation 
        verify(0, st.num_orders(), "Invalid number of orders");
        int order_num = st.create_order("customer@mavmart.com");
        verify(0, order_num, "Invalid order number generated");
        verify(0, st.order(order_num).num_product_orders(), "Invalid number of product orders in store order");
        Product_order po{"Sandwich", 3.50, 1};
        st.add_to_order(order_num, po);
        verify(1, st.order(order_num).num_product_orders(), "Invalid number of product orders in store order");
        verify("Sandwich", st.order(order_num).product_order(0).name(), "Invalid name");
        verify(3.50, st.order(order_num).product_order(0).price(), "Invalid price");
        verify(1, st.order(order_num).product_order(0).quantity(), "Invalid quantity");

    // Test operator<<
        std::ostringstream oss;
        oss << st;
        verify("0) Sandwich ($3.50)\n", oss.str(), "Operator<<");

    } catch(std::exception e) {
        std::cerr << "FAIL: " << classname << " exception during test vector " << test_vector << ": " << e.what() << std::endl;
        result_code |= test_vector;
    }

    return result_code;
}

