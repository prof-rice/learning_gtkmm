#include "mainwin.h"
#include "dialogs.h"
#include "rental_site.h"
#include <vector>

Mainwin::Mainwin() : _controller{Controller{}} {

    // Provide parent window to dialogs to avoid discouraging warnings
    Dialogs::set_window(*this);

    // /////////////////
    // G U I   S E T U P
    // /////////////////

    set_default_size(720, 400);

    // Put a vertical box container as the Window contents
    Gtk::Box *vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
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

    //         N E W   R E N T A L   S I T E
    // Append New to the File menu
    Gtk::MenuItem *menuitem_new = Gtk::manage(new Gtk::MenuItem("_New", true));
    menuitem_new->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_new_rental_site_click));
    filemenu->append(*menuitem_new);

    //         O P E N   R E N T A L   S I T E
    // Append Open to the File menu
    Gtk::MenuItem *menuitem_open = Gtk::manage(new Gtk::MenuItem("_Open", true));
    menuitem_open->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_file_open_click));
    filemenu->append(*menuitem_open);

    //         S A V E   R E N T A L   S I T E
    // Append Save to the File menu
    Gtk::MenuItem *menuitem_save = Gtk::manage(new Gtk::MenuItem("_Save", true));
    menuitem_save->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_file_save_click));
    filemenu->append(*menuitem_save);

    //         S A V E   A S   R E N T A L   S I T E
    // Append New to the File menu
    Gtk::MenuItem *menuitem_save_as = Gtk::manage(new Gtk::MenuItem("Save _As", true));
    menuitem_save_as->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_file_save_as_click));
    filemenu->append(*menuitem_save_as);

    //         Q U I T
    // Append Quit to the File menu
    Gtk::MenuItem *menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
    menuitem_quit->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_quit_click));
    filemenu->append(*menuitem_quit);

    //     V E H I C L E
    // Create a Vehicle menu and add to the menu bar
    Gtk::MenuItem *menuitem_vehicle = Gtk::manage(new Gtk::MenuItem("_Vehicle", true));
    menubar->append(*menuitem_vehicle);
    Gtk::Menu *vehiclemenu = Gtk::manage(new Gtk::Menu());
    menuitem_vehicle->set_submenu(*vehiclemenu);

    //           N E W   V E H I C L E
    // Append New Vehicle to the Vehicle menu
    Gtk::MenuItem *menuitem_new_vehicle = Gtk::manage(new Gtk::MenuItem("_New", true));
    menuitem_new_vehicle->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_new_vehicle_click));
    vehiclemenu->append(*menuitem_new_vehicle);

    //           L I S T   V E H I C L E S
    // Append New Vehicle to the Vehicle menu
    Gtk::MenuItem *menuitem_list_vehicles = Gtk::manage(new Gtk::MenuItem("_List", true));
    menuitem_list_vehicles->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_list_vehicles_click));
    vehiclemenu->append(*menuitem_list_vehicles);

    //           R E N T   V E H I C L E
    // Append New Vehicle to the Vehicle menu
    Gtk::MenuItem *menuitem_rent_vehicle = Gtk::manage(new Gtk::MenuItem("_Rent", true));
    menuitem_rent_vehicle->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_rent_vehicle_click));
    vehiclemenu->append(*menuitem_rent_vehicle);

    //           R E T U R N   V E H I C L E
    // Append New Vehicle to the Vehicle menu
    Gtk::MenuItem *menuitem_return_vehicle = Gtk::manage(new Gtk::MenuItem("R_eturn", true));
    menuitem_return_vehicle->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_return_vehicle_click));
    vehiclemenu->append(*menuitem_return_vehicle);

    //     R E N T E R
    // Create a Renter menu and add to the menu bar
    Gtk::MenuItem *menuitem_renter = Gtk::manage(new Gtk::MenuItem("_Renter", true));
    menubar->append(*menuitem_renter);
    Gtk::Menu *rentermenu = Gtk::manage(new Gtk::Menu());
    menuitem_renter->set_submenu(*rentermenu);

    //           N E W   R E N T E R
    // Append New Renter to the Renter menu
    Gtk::MenuItem *menuitem_new_renter = Gtk::manage(new Gtk::MenuItem("_New", true));
    menuitem_new_renter->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_new_renter_click));
    rentermenu->append(*menuitem_new_renter);

    //           L I S T   R E N T E R S
    // Append List Renters to the Renter menu
    Gtk::MenuItem *menuitem_list_renters = Gtk::manage(new Gtk::MenuItem("_List", true));
    menuitem_list_renters->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_list_renters_click));
    rentermenu->append(*menuitem_list_renters);

    //     H E L P
    // Create a Help menu and add to the menu bar
    Gtk::MenuItem *menuitem_help = Gtk::manage(new Gtk::MenuItem("_Help", true));
    menubar->append(*menuitem_help);
    Gtk::Menu *helpmenu = Gtk::manage(new Gtk::Menu());
    menuitem_help->set_submenu(*helpmenu);

    //           H E L P
    // Append Help to the Help menu
    Gtk::MenuItem *menuitem_help_ = Gtk::manage(new Gtk::MenuItem("_Help", true));
    menuitem_help_->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_help_click));
    helpmenu->append(*menuitem_help_);

    //           T E S T
    // Add 4 vehicles and 3 renters
    Gtk::MenuItem *menuitem_test_ = Gtk::manage(new Gtk::MenuItem("_Test", true));
    menuitem_test_->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_test_click));
    helpmenu->append(*menuitem_test_);

    //           A B O U T
    // Append About to the Help menu
    Gtk::MenuItem *menuitem_about = Gtk::manage(new Gtk::MenuItem("_About", true));
    menuitem_about->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_about_click));
    helpmenu->append(*menuitem_about);

    // /////////////
    // T O O L B A R
    // Add a toolbar to the vertical box below the menu
    Gtk::Toolbar *toolbar = Gtk::manage(new Gtk::Toolbar);
    vbox->add(*toolbar);

    //     N E W
    // Add a new icon
    Gtk::Image *new_image = Gtk::manage(new Gtk::Image{"new.png"});
    Gtk::ToolButton *new_button = Gtk::manage(new Gtk::ToolButton(*new_image));
    new_button->set_tooltip_markup("Create a new rental site");
    new_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_new_rental_site_click));
    toolbar->append(*new_button);

    //     O P E N
    // Add a open icon
    Gtk::Image *open_image = Gtk::manage(new Gtk::Image{"open.png"});
    Gtk::ToolButton *open_button = Gtk::manage(new Gtk::ToolButton(*open_image));
    open_button->set_tooltip_markup("Open a rental site");
    open_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_file_open_click));
    toolbar->append(*open_button);

    //     S A V E
    // Add a save icon
    Gtk::Image *save_image = Gtk::manage(new Gtk::Image{"save.png"});
    Gtk::ToolButton *save_button = Gtk::manage(new Gtk::ToolButton(*save_image));
    save_button->set_tooltip_markup("Save the current rental site");
    save_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_file_save_click));
    toolbar->append(*save_button);

    Gtk::SeparatorToolItem *sep0 = Gtk::manage(new Gtk::SeparatorToolItem());
    toolbar->append(*sep0);

    //     N E W   V E H I C L E
    // Add a new vehicle icon
    Gtk::Image *new_vehicle_image = Gtk::manage(new Gtk::Image{"new_vehicle.png"});
    Gtk::ToolButton *new_vehicle_button = Gtk::manage(new Gtk::ToolButton(*new_vehicle_image));
    new_vehicle_button->set_tooltip_markup("Create a new vehicle");
    new_vehicle_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_new_vehicle_click));
    toolbar->append(*new_vehicle_button);

    //     L I S T   V E H I C L E S
    // List vehicles icon
    Gtk::Image *list_vehicles_image = Gtk::manage(new Gtk::Image{"list_vehicles.png"});
    Gtk::ToolButton *list_vehicles_button = Gtk::manage(new Gtk::ToolButton(*list_vehicles_image));
    list_vehicles_button->set_tooltip_markup("List all vehicles");
    list_vehicles_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_list_vehicles_click));
    toolbar->append(*list_vehicles_button);

    //     R E N T   V E H I C L E
    // Add a icon for renting a vehicle
    rent_vehicle_on_image = Gtk::manage(new Gtk::Image{"rent_vehicle_on.png"});
    rent_vehicle_off_image = Gtk::manage(new Gtk::Image{"rent_vehicle_off.png"});
    rent_vehicle = Gtk::manage(new Gtk::ToolButton(*rent_vehicle_on_image));
    rent_vehicle->set_tooltip_markup("Rent a vehicle");
    rent_vehicle->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_rent_vehicle_click));
    toolbar->append(*rent_vehicle);

    //     R E T U R N   V E H I C L E
    // Add a icon for returning a vehicle
    return_vehicle_on_image = Gtk::manage(new Gtk::Image{"return_vehicle_on.png"});
    return_vehicle_off_image = Gtk::manage(new Gtk::Image{"return_vehicle_off.png"});
    return_vehicle = Gtk::manage(new Gtk::ToolButton(*return_vehicle_on_image));
    return_vehicle->set_tooltip_markup("Return a vehicle");
    return_vehicle->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_return_vehicle_click));
    toolbar->append(*return_vehicle);

    Gtk::SeparatorToolItem *sep1 = Gtk::manage(new Gtk::SeparatorToolItem());
    toolbar->append(*sep1);

    //     N E W   R E N T E R
    // Add a new renter icon
    Gtk::Image *new_renter_image = Gtk::manage(new Gtk::Image{"new_renter.png"});
    Gtk::ToolButton *new_renter_button = Gtk::manage(new Gtk::ToolButton(*new_renter_image));
    new_renter_button->set_tooltip_markup("Create a new renter");
    new_renter_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_new_renter_click));
    toolbar->append(*new_renter_button);

    //     L I S T   R E N T E R S
    // List renters icon
    Gtk::Image *list_renters_image = Gtk::manage(new Gtk::Image{"list_renters.png"});
    Gtk::ToolButton *list_renters_button = Gtk::manage(new Gtk::ToolButton(*list_renters_image));
    list_renters_button->set_tooltip_markup("List all renters");
    list_renters_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_list_renters_click));
    toolbar->append(*list_renters_button);

 
    //     Q U I T
    // Add a icon for quitting
    Gtk::ToolButton *quit_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::QUIT));
    quit_button->set_tooltip_markup("Exit RVMS");
    quit_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_quit_click));
    Gtk::SeparatorToolItem *sep = Gtk::manage(new Gtk::SeparatorToolItem());
    sep->set_expand(true);  // The expanding sep forces the Quit button to the right
    toolbar->append(*sep);
    toolbar->append(*quit_button);

    // P U B L I C A T I O N   T A B L E

    _tree_model = Gtk::ListStore::create(_columns);

    _tree_view.set_model(_tree_model);

    _tree_view.append_column("Year", _columns.m_year);
    _tree_view.append_column("Make", _columns.m_make);
    _tree_view.append_column("Model", _columns.m_model);
    _tree_view.append_column("Body Style", _columns.m_body_style);
    _tree_view.append_column("Renter", _columns.m_renter);
    _tree_view.append_column("Driver's License", _columns.m_renter_dl);
    _tree_view.append_column("Phone Number", _columns.m_renter_phone);

    _swindow.add(_tree_view);
    _swindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    _swindow.set_hexpand(true);
    _swindow.set_vexpand(true);

    vbox->pack_start(_swindow);


/* Saved for extreme bonus
    // S T A T U S   B A R   D I S P L A Y
    // Provide a status bar for program messages
    msg = Gtk::manage(new Gtk::Label());
    msg->set_hexpand(true);
    vbox->add(*msg);
*/

    // Make the box and everything in it visible
    vbox->show_all();
}

Mainwin::~Mainwin() { }

// /////////////////
// C A L L B A C K S
// /////////////////

void Mainwin::on_new_rental_site_click() { // Create a new rental site
   _controller.execute_cmd(18);
}

void Mainwin::on_file_open_click() {       // Open a rental site
    _controller.execute_cmd(8);
}

void Mainwin::on_file_save_click() {       // Save a rental site
    _controller.execute_cmd(17);
}

void Mainwin::on_file_save_as_click() {    // Save as rental site
    _controller.execute_cmd(7);
}

void Mainwin::on_new_vehicle_click() {     // Create a new vehicle
    int index_before = _controller.vehicles().size();
    _controller.execute_cmd(1);
    int index_after = _controller.vehicles().size();
    for (int i=index_before; i<index_after; ++i) add_row(i);
}

void Mainwin::on_list_vehicles_click() {   // List all vehicles
    _controller.execute_cmd(2);
}

void Mainwin::on_rent_vehicle_click() {    // Rent a vehicle
    _controller.execute_cmd(3);
    update_rows();
}

void Mainwin::on_return_vehicle_click() {  // Return a vehicle
    _controller.execute_cmd(4);
    update_rows();
}

void Mainwin::on_new_renter_click() {      // Create a new renter
    _controller.execute_cmd(5);
}

void Mainwin::on_list_renters_click() {    // List all renters
    _controller.execute_cmd(6);
}

void Mainwin::on_help_click() {            // Display help
    _controller.execute_cmd(9);
}

void Mainwin::on_test_click() {            // Add 4 vehicles and 3 models
    int index_before = _controller.vehicles().size();
    _controller.execute_cmd(42);
    int index_after = _controller.vehicles().size();
    for (int i=index_before; i<index_after; ++i) add_row(i);
}

void Mainwin::on_about_click() {
    Glib::ustring s = "<span size='24000' weight='bold'>Rental Vehicle Management System</span>\n<span size='large'>Copyright 2018 by George F. Rice</span>\n<span size='small'>Licensed under Creative Commons Attribution 4.0 International</span>";
    Gtk::MessageDialog dlg(*this, s, true, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
    dlg.run();
}

void Mainwin::on_quit_click() {      // Exit the program
    hide();
}

// /////////////////
// U T I L I T I E S
// /////////////////

void Mainwin::add_row(int index) {
    // Add a new row to the tree model to hold the new publication
    Gtk::TreeModel::Row row = *(_tree_model->append());

    // Load the data into the new row
    std::vector<std::string> record = _controller.vehicles()[index];

    row[_columns.m_vehicle_id] = index;
    row[_columns.m_year] = record[0];
    row[_columns.m_make] = record[1];
    row[_columns.m_model] = record[2];
    row[_columns.m_body_style] = record[3];
    row[_columns.m_renter] = record[4];
    row[_columns.m_renter_dl] = record[5];
    row[_columns.m_renter_phone] = record[6];
}


void Mainwin::update_rows() {
    Gtk::TreeIter iter = _tree_model->get_iter("0");
    std::vector<std::vector<std::string>> records = _controller.vehicles();
    for(auto record : records) {
        (*iter)[_columns.m_renter] = record[4];
        (*iter)[_columns.m_renter_dl] = record[5];
        (*iter)[_columns.m_renter_phone] = record[6];
        iter++;
    }
}


