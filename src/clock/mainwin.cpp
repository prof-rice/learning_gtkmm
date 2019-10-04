// File: mainwin.cpp

#include "mainwin.h"
#include <chrono>
#include <ctime> 

Mainwin::Mainwin() {

    // /////////////////
    // G U I   S E T U P
    // /////////////////

    // Set the x,y size of the window in pixels, and the title
    set_default_size(180, 40);
    set_title("Clock");

    // Add a VBox (box containing vertically-stacked widgets) to the Window
    // This allows many widgets (menu, toolbar, data area, status bar, etc.)
    //   to be added to the main window, as Gtk::Window can contain only one
    Gtk::Box *vbox = Gtk::manage(new Gtk::VBox);
    add(*vbox);

    // Create a Label to display the time and add to the VBox
    msg = Gtk::manage(new Gtk::Label);
    vbox->add(*msg);

    // Connect the "timeout" signal to the on_timer method
    // Call it once every 1000 milliseconds until it returns false
    Glib::signal_timeout().connect([this] {return this->on_timer();}, 1000);
    // Prior to lambdas, we would have done this instead:
    //    Glib::signal_timeout().connect(sigc::mem_fun(*this, &Mainwin::on_timer), 1000);

    // Initialize the display during the first second
    on_timer();

    // Make the VBox and everything in it visible on-screen
    vbox->show_all();
}

// Always declare a virtual destructor
Mainwin::~Mainwin() { }

// /////////////////
// C A L L B A C K S
// /////////////////

// On_timer update the time in the main window
bool Mainwin::on_timer() {
    // Get the current time in time_t format
    auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); 

    // Set the text displayed in the Label we added to the Window to the current local time
    msg->set_text(std::ctime(&timenow));

    // Returning true enables this periodic event to recur after the elapsed time specified above
    return true; 
}


