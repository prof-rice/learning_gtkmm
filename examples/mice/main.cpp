#include "mainwin.h"
#include <gtkmm.h>

int main (int argc, char *argv[])
{
  Glib::RefPtr<Gtk::Application> app = 
    Gtk::Application::create(argc, argv, "edu.uta.cse1325.mice");

  // Instance a Window
  Mainwin win;

  //Show the window and returns when it is closed or hidden
  return app->run(win);
}

