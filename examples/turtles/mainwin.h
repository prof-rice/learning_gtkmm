#include <gtkmm.h>
#include "turtlepad.h"

class Mainwin : public Gtk::Window {
    public:
        Mainwin();
        virtual ~Mainwin();
    protected:
        Turtlepad *pad;
}; 

