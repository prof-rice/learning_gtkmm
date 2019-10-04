#ifndef __MAINWIN_H
#define __MAINWIN_H

#include <gtkmm.h>

const int MINN =   1;  // Smallest possible number to guess
const int MAXX = 100;  // Largest  possible number to guess

class Mainwin : public Gtk::Window
{
    public:
        Mainwin();
        virtual ~Mainwin();
    protected:
        void on_new_game_click();            // Create a new game
        void on_guess_activated();           // Enter a guess
        void on_about_click();               // Display About dialog
        void on_quit_click();                // Exit the game
        void set_status(std::string status); // Update the label
    private:
        Gtk::Label* msg;                     // Status message display
        Gtk::Entry* guess;                   // Player's guess
        Gtk::Button* button;                 // "Enter guess" button
        int _number;                         // The number to be guessed
        int _min;                            // The min value still possible
        int _max;                            // The max value still possible
};
#endif 

