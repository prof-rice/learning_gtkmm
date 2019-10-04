#include "mainwin.h"
#include <fstream>

Main_window::Main_window() {
    set_default_size(400, 200);
    set_title("Tic Tac Toe");

    // Put a vertical box container as the Window contents
    Gtk::Box *vbox = Gtk::manage(new Gtk::VBox);
    add(*vbox);

    // ///////
    // M E N U
    // Add a menu bar as the top item in the vertical box
    Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar());
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);

    //     F I L E
    // Create a File menu and add to the menu bar
    Gtk::MenuItem *menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
    menubar->append(*menuitem_file);
    Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);

    //         N E W
    // Append New to the File menu
    Gtk::MenuItem *menuitem_new = Gtk::manage(new Gtk::MenuItem("_New", true));
    // Classically,that is, pre-lambda, the next line would be
    // menuitem_new->signal_activate().connect(
    //    sigc::mem_fun(*this, &Main_window::on_new_game_click));
    menuitem_new->signal_activate().connect([this] {this->on_new_game_click();});
    filemenu->append(*menuitem_new);

    //         Q U I T
    // Append Quit to the File menu
    Gtk::MenuItem *menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
    menuitem_quit->signal_activate().connect([this] {this->close();});
    filemenu->append(*menuitem_quit);

    // /////////////
    // T O O L B A R
    // Add a toolbar to the vertical box below the menu
    Gtk::Toolbar *toolbar = Gtk::manage(new Gtk::Toolbar);
    vbox->add(*toolbar);

    //     New
    // Start a new game
    Gtk::ToolButton *new_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::NEW));
    new_button->set_tooltip_markup("Start a new game");
    new_button->signal_clicked().connect([this] {this->on_new_game_click();});
    toolbar->append(*new_button);


    // C O N T E N T   D I S P L A Y
    // Show a 3x3 grid of reactive buttons representing the game board
    for (int x=0; x<3; ++x) {
        Gtk::HBox* hbox = Gtk::manage(new Gtk::HBox);
        hbox->set_hexpand(true);
        for (int y=0; y<3; ++y) {
            auto position = Gtk::manage(new Gtk::Button);
            board.push_back(position);
            position->signal_clicked().connect(
                [this, x, y] {this->on_button_click(x, y);});
            hbox->add(*position);
        }
        vbox->add(*hbox);
    }
   
    // S T A T U S   B A R   D I S P L A Y
    // Provide a status bar for game messages
    msg = Gtk::manage(new Gtk::Label());
    msg->set_hexpand(true);
    vbox->add(*msg);

    // Make the box and everything in it visible
    vbox->show_all();

    // Start a new game
    on_new_game_click();
}

Main_window::~Main_window() { }

// /////////////////
// C A L L B A C K S
// /////////////////

void Main_window::on_button_click(int x, int y) {
    Gtk::Image* image;
    if(current_player) image = Gtk::manage(new Gtk::Image{"player_1.png"});
    else image = Gtk::manage(new Gtk::Image{"player_0.png"});
    board[x*3+y]->set_image(*image);
    current_player = 1-current_player;
    set_status();
}

void Main_window::on_new_game_click() {
    // Announce who moves first
    current_player = std::rand() % 2;
    set_status();

    // Clear the board
    for (int x=0; x<3; ++x) {
        for (int y=0; y<3; ++y) {
            Gtk::Image* image = Gtk::manage(new Gtk::Image{"player_none.png"});
            board[x*3+y]->set_image(*image);
        }
    }
}

// /////////////////
// U T I L I T I E S
// /////////////////

void Main_window::set_status() {
    std::string s = (current_player) ? "X" : "O";
    msg->set_text("Player " + s + "'s move");
}


