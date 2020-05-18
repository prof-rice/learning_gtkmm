#ifndef MAINWIN_H
#define MAINWIN_H
#include <iostream>
#include <gtkmm.h>

class Mainwin : public Gtk::Window {
    public:
        Mainwin();
        virtual ~Mainwin();
    protected:
        bool update_mouseclick(GdkEventButton* event,std::string name);
    private:
        Gtk::Label* label;
};

#endif