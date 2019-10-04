#include "main_window.h"
#include <iostream>

Main_window::Main_window() {

    // /////////////////
    // G U I   S E T U P
    // /////////////////

    set_default_size(200, 100);
    set_title("Double-Click");

    // Add a button to the main window
    Gtk::Button* button = Gtk::manage(
        new Gtk::Button{"Click me!"});
    add(*button);
    show_all();

    // Enable button press events, then 
    // connect our 2 handler methods via lambdas
    button->add_events(Gdk::BUTTON_PRESS_MASK); 
    button->signal_button_press_event().connect(
        [this] (GdkEventButton* event) 
            {return this->on_button_press(event);});
    button->signal_clicked().connect(
        [this] {this->on_button_click();}); 
}

Main_window::~Main_window() { }

// /////////////////
// C A L L B A C K S
// /////////////////

void Main_window::on_button_click() {
    std::cout << "Button 1 clicked! (special)" << std::endl;
}

bool Main_window::on_button_press(GdkEventButton* event) {
    if(event->type == GDK_BUTTON_PRESS) {
        std::cout << "Button " << event->button 
                  << " clicked!" << std::endl;
    } else if (event->type == GDK_DOUBLE_BUTTON_PRESS) {
         std::cout << "Button " << event->button 
                   << " double-clicked!" << std::endl;
    } else if (event->type == GDK_TRIPLE_BUTTON_PRESS) {
         std::cout << "Button " << event->button 
                   << " triple-clicked!" << std::endl;
    } else if (event->type == GDK_BUTTON_RELEASE) {
         std::cout << "Button " << event->button 
                   << " released!" << std::endl;
    } else if (event->type == GDK_KEY_PRESS) {
         std::cout << "Key " << event->button 
                   << " pressed!" << std::endl;
    } else if (event->type == GDK_KEY_RELEASE) {
        std::cout << "Key " << event->button 
                  << " released!" << std::endl;
    } else {
        return false;
    }
    return true;
}

// /////////////////
// U T I L I T I E S
// /////////////////

