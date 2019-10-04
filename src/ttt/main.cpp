#include "mainwin.h"
#include <gtkmm.h>

int main (int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "lg.tic.tac.toe");
    Main_window win;
    return app->run(win);
}

