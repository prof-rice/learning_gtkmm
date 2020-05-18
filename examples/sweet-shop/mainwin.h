#ifndef MAINWIN_H
#define MAINWIN_H

#include <gtkmm.h>
#include "store.h"

const std::string VERSION{"0.1.0"};
const std::string APP_NAME{"edu.uta.cse1325.sweets.v0_1_0"};

class Mainwin : public Gtk::Window
{
    public:
        Mainwin();
        Mainwin(Store& store);
        virtual ~Mainwin();
    protected:
        void on_new_store_click();            // Create a new store
        void on_add_sweet_click();            // Create a new sweet product
        void on_list_sweets_click();          // List all sweet products
        void on_place_order_click();          // Place a new order
        void on_list_orders_click();          // Select an order to list
        void on_about_click();                // Display About dialog
        void on_quit_click();                 // Exit the program
    private:
        Store *_store;                        // Current model
        void reset_sensitivity();             // Reset command sensitivity based on data

        // Menu items
        Gtk::MenuItem *menuitem_add_sweet;    // Sweets > Add
        Gtk::MenuItem *menuitem_list_sweets;  // Sweets > List
        Gtk::MenuItem *menuitem_place_order;  // Orders > Place
        Gtk::MenuItem *menuitem_list_orders;  // Orders > List

        // Tool bar buttons
        Gtk::ToolButton* add_sweet_button;    // Add a new sweet
        Gtk::ToolButton* list_sweets_button;  // List all sweets
        Gtk::ToolButton* place_order_button;  // Add an order
        Gtk::ToolButton* list_orders_button;  // Select an order to list

        // Display widgets
        Gtk::Label *data;                     // Information display
        Gtk::Label *msg;                      // Status message display

};
#endif 

