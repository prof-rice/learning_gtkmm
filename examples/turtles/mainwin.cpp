#include "mainwin.h"

Mainwin::Mainwin() {
    set_default_size(400, 400); 
    set_title("Turtle Graphics");

    pad = Gtk::manage(new Turtlepad);
    add(*pad);
    pad->show();

    // Create "star" drawing
    pad->penDown();
    for (double d=0; d<20; ++d) {
        pad->forward(d*15.0);
        pad->turn(144);
    }
}

Mainwin::~Mainwin() { } 

