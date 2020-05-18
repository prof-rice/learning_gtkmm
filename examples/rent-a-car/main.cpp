#include <gtkmm.h>
#include "mainwin.h"

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "edu.uta.cse1325.rvms");
    Mainwin win;
    win.set_title("Rental Vehicle Management System");
    return app->run(win);
}
