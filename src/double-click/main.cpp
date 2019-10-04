#include "main_window.h"
#include <gtkmm.h>

int main (int argc, char *argv[])
{
    // Make a new app
    auto app = Gtk::Application::create(argc, argv, "lg.double-click");

    // Instance a Window
    Main_window win;

    // Tell the app to run the Window
    return app->run(win);
}

