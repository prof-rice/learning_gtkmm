#include "mainwin.h"
#include <ctime>

Mainwin::Mainwin() {

    // /////////////////
    // G U I   S E T U P
    // /////////////////

    set_default_size(400, 200);
    set_title("Guesser");

    // Put a vertical box container as the Window contents
    // Gtk::manage tells gtkmm to delete the box when the window closes
    // Gtk::VBox* vbox = Gtk::manage(new Gtk::VBox{});
    Gtk::Box* vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    add(*vbox);

    // Add a label to tell the player the status of the game
    // Center the text and expand it horizontally to fill the main window
    // Then add it to the vertical box (VBox) in the main window
    msg = Gtk::manage(new Gtk::Label("", Gtk::ALIGN_CENTER));
    msg->set_hexpand(true);
    msg->set_vexpand(true);
    vbox->add(*msg);

    // Create a text box to receive the player's guess
    // When the player hits Enter ("activate"), call the on_guess_activated() method
    guess = Gtk::manage(new Gtk::Entry());
    guess->signal_activate().connect([this] {this->on_guess_activated();});
    vbox->add(*guess);

    // Create a button that can also be clicked to enter a guess
    button = Gtk::manage(new Gtk::Button{"Enter Guess"});
    button->signal_clicked().connect([this] {this->on_guess_activated();});
    vbox->add(*button);

    // Make the vbox and everything in it visible
    vbox->show_all();

    // Start a new game
    on_new_game_click();
}

Mainwin::~Mainwin() { }

// /////////////////
// C A L L B A C K S
// /////////////////

// This is called from the constructor for the initial game, 
// and when File > New is selected by the player
void Mainwin::on_new_game_click() {

    // Initialize the data model
    srand (time(NULL));
    _min = MINN - 1;
    _max = MAXX + 1;
    _number = (rand() % (_max-_min)) + _min;
    set_status("Guess a number between " + std::to_string(MINN) + " and " + std::to_string(MAXX));
    guess->set_sensitive(true);  // Start accepting guesses!
    button->set_sensitive(true);
}

// This is called when the user presses Enter in the guess entry box
void Mainwin::on_guess_activated() {
    try {
        int i = std::stoi(guess->get_text());
        if (i < _number) {
            _min = i;
            set_status("Too low! Guess again");
        } else if (i > _number) {
            _max = i;
            set_status("Too high! Guess again");
        } else {
            _min = _number-1;
            _max = _number+1;
            set_status("THAT'S IT!!!");
            guess->set_sensitive(false);  // No more guesses accepted!
            button->set_sensitive(false);
        }
    } catch (std::exception e) {
        guess->set_text("### Invalid ###");
    }
    guess->set_text("");
}

void Mainwin::on_quit_click() {
    hide();
}

void Mainwin::on_about_click() {
    Glib::ustring s = "<span size='24000' weight='bold'>Guessing Game</span>\n<span size='large'>Copyright 2019 by George F. Rice</span>\n<span size='small'>Licensed under the Gnu General Public License 3.0\n    https://www.gnu.org/licenses/gpl-3.0.en.html</span>";
    Gtk::MessageDialog dlg(*this, s, true, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
    dlg.run();
}

// /////////////////
// U T I L I T I E S
// /////////////////

// Update the status display
void Mainwin::set_status(std::string message) {
    const int INTS_PER_ROW = 10;
    int ints_on_row = INTS_PER_ROW;
    std::string s = "<big><b>" + message + "</b></big>\n";
    if (_min < MINN) s += "<span fgcolor='black'>"; else s+= "<span fgcolor='grey'>";
    for(int i=MINN; i<=MAXX; ++i) {
        if (i == _max) s += "</span><span fgcolor='grey'>";
        s += " " + std::to_string(i);
        if (i == _min) s += "</span><span fgcolor='black'>";
        if (i == MAXX) s += "</span>";
        if (--ints_on_row == 0) {s += '\n'; ints_on_row = INTS_PER_ROW;}
    }
    msg->set_markup(s);
}


