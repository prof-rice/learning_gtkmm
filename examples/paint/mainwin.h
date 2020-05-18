#ifndef MAINWIN_H
#define MAINWIN_H

#include "canvas.h"
#include <gtkmm.h>


class Mainwin : public Gtk::Window {
    public:
        Mainwin();
        virtual ~Mainwin();
    protected:
        void on_new_click();                 // Start a new drawing
        void on_open_click();                // Open an existing drawing
        void on_save_click();                // Save the drawing
        void on_save_as_click();             // Save the drawing to a new filename
        void on_quit_click();                // Exit the program
        void on_undo_click();                // Undo creation of the last shape
        void on_color_click();               // Set the pen color
        void on_width_click();               // Set the pen width
        void on_dash_pattern_click();        // Set dash pattern
        void on_pen_mode_segment_click();    // Set segment mode
        void on_pen_mode_contiguous_click(); // Set contiguous mode
        void on_pen_mode_freehand_click();   // Set freehand mode
        void on_about_click();               // Show the About dialog
    private:
        Canvas *canvas;
};
#endif

