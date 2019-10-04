#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <gtkmm.h>
#include <vector>

class Main_window : public Gtk::Window
{
    public:
        Main_window();
        virtual ~Main_window();
    protected:
        void on_button_click(int x, int y); // Respond to toolbar button click
        void on_new_game_click();           // Display dialog to set max die roll
        void set_status();                  // Update the status bar
    private:
        std::vector<Gtk::Button*> board; // Game board
        Gtk::Label *msg;                 // Status message display
        int current_player;              // 0 or 1, whose turn it is to move
};
#endif 

