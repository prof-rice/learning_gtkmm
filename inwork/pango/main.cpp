#include "mainwin.h"
#include <gtkmm.h>

int main (int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "com.lg.guesser.v1_0");
    Mainwin win;
    return app->run(win);
}

