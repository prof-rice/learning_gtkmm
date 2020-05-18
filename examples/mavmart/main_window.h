#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>
#include "controller.h"

class Main_window : public Gtk::Window
{
    public:
        Main_window();
        virtual ~Main_window();
    protected:
        void on_new_click();             // Create a new game
        void on_open_click();            // Create a new game
        void on_save_click();            // Create a new game
        void on_save_as_click();         // Create a new game
        void on_add_product_click();     // Create a new game
        void on_list_products_click();   // Create a new game
        void on_add_order_click();       // Create a new game
        void on_list_orders_click();     // Create a new game
        void on_about_click();           // Display About dialog
        void on_help_click();            // Display About dialog
        void on_test_click();            // Display About dialog
        void on_quit_click();            // Exit the game
    private:
        void set_data();                      // Update the data area of main window
        Controller* controller;               // Current store controller
        Gtk::Label *data;                   // Display of sticks on game board
        Gtk::Label *msg;                      // Status message display

/*
        Gtk::ToolButton *button1;             // Button to select 1 stick
        Gtk::Image *button1_on_image;         //   Image when active
        Gtk::Image *button1_off_image;        //   Image when inactive
        Gtk::ToolButton *button2;             // Button to select 2 sticks
        Gtk::Image *button2_on_image;
        Gtk::Image *button2_off_image;
        Gtk::ToolButton *button3;             // Button to select 3 sticks
        Gtk::Image *button3_on_image;
        Gtk::Image *button3_off_image;
        Gtk::ToggleToolButton *computer_player;  // Button to enable robot
*/
};
#endif 

