#include "mainwin.h"
#include <gtkmm.h>

// Spirograph equations courtesy of Linux Gazette, https://linuxgazette.net/133/luana.html
// double fx(double R, double r, double p, double t) {return (double)((R-r)*cos(t)+p*cos((R-r)*t/r));}
// double fy(double R, double r, double p, double t) {return (double)((R-r)*sin(t)+p*sin((R-r)*t/r));}

int main(int argc, char** argv) {
   // Create the application
   auto app = Gtk::Application::create(argc, argv, "edu.uta.cse1325.paint");

   // Instance a window
   Mainwin win;

   // Give control to gtkmm
   return app->run(win);
}
