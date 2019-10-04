#include "mainwin.h"
#include <iostream>

Mainwin::Mainwin() {

    // /////////////////
    // G U I   S E T U P
    // /////////////////

    set_default_size(400, 200);
    set_title("Scrolling Reactive Grid Example");

    // Put a vertical box container as the Window contents
    Gtk::Box *vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    add(*vbox);

    // ///////////////////////
    // D A T A   D I S P L A Y
    // Provide a scrolling grid of buttons that respond to clicks
    Gtk::Grid* grid = Gtk::manage(new Gtk::Grid());

    // Create the array of buttons
    for(int i=0; i<10; ++i) {
        for(int j=0; j<10; ++j) {

            // Define the text to display on each button
            std::string s = "Button " + std::to_string(i) 
                                + ',' + std::to_string(j);

            // Create each button
            Gtk::Button* button = Gtk::manage(new Gtk::Button{s});

            // Connect each button to a lambda that adapts to the callback
            button->signal_clicked().connect(
                [this, i, j] {this->on_button_clicked(i,j);});

            // Attach the new button to the grid
            grid->attach(*button, i, j, 1, 1);
        }
    }

    // Create a scrolling pane with the vertical scroll bar always showing
    // and the horizontal scroll bar only showing when needed
    Gtk::ScrolledWindow* scroller = Gtk::manage(new Gtk::ScrolledWindow);
    scroller->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_ALWAYS);

    // Add grid inside scrolling pane, and set pane to expand and contract
    // as the window is resized (other elements would remain fixed size)
    scroller->add(*grid);
    scroller->set_hexpand(true);
    scroller->set_vexpand(true);

    // Add the scrolling pane in which the grid resides to the vertical box
    vbox->add(*scroller);
    
    // Make the box and everything in it visible
    vbox->show_all();
}

Mainwin::~Mainwin() { }

// /////////////////
// C A L L B A C K S
// /////////////////
void Mainwin::on_button_clicked(int x, int y) {
    std::cout << "Button " << x 
                    << ',' << y << " clicked!" << std::endl;
}

// /////////////////
// U T I L I T I E S
// /////////////////

