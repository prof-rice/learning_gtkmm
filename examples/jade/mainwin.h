#ifndef MAINWIN_H
#define MAINWIN_H

#include <gtkmm.h>
#include "store.h"

class Mainwin : public Gtk::Window
{
    public:
        Mainwin();
        virtual ~Mainwin();
    protected:
        void on_open_click();            // Open saved data
        void on_save_click();            // Save data
        void on_quit_click();            // Exit the program
        void on_view_orders_click();     // Select an order to view
        void on_view_products_click();   // View all products
        void on_create_order_click();    // Create a new order
        void on_create_coffee_click();   // Create a new coffee product
        void on_create_donut_click();    // Create a new donut product
        void on_list_customers_click();  // List all customers
        void on_new_customer_click();    // Create a new customer
        void on_test_click();            // "Easter Egg" command
        void on_about_click();           // About dialog
    private:
        Store _store;
        Gtk::Label *msg;                      // Status message display
        Gtk::MenuItem *menuitem_new_order;    // Create -> Order
        Gtk::MenuItem *menuitem_new_coffee;   // Create -> Coffee
        Gtk::MenuItem *menuitem_new_donut;    // Create -> Donut
};
#endif 

