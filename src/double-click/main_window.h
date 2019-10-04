// mainwin.h

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>

class Main_window : public Gtk::Window
{
    public:
        Main_window();
        virtual ~Main_window();
    protected:
        void on_button_click();                      // Respond to button clicks
        bool on_button_press(GdkEventButton* event); // Handle button events
    private:
};
#endif 

