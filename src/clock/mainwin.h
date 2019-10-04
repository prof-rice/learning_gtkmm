// File: mainwin.h

#ifndef __MAINWIN_H
#define __MAINWIN_H

#include <gtkmm.h>

class Mainwin : public Gtk::Window {
    public:
        Mainwin();                 // Adds widgets and signals
        virtual ~Mainwin();        // Deletes widgets on window close
    protected:
        bool on_timer();           // Called every second
    private:
        Gtk::Label *msg;           // Time display
};
#endif 

