#include "mainwin.h"
#include <exception>
#include <stdexcept>
#include <iostream>
#include <sstream>

Mainwin::Mainwin() {

    // /////////////////
    // G U I   S E T U P
    // /////////////////

    set_default_size(800, 600);

    // Put a vertical box container as the Window contents
    Gtk::Box *vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    add(*vbox);

    // ///////
    // M E N U
    // Add a menu bar as the top item in the vertical box
    Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar());
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);

    //
    //     F I L E
    // Create a File menu and add to the menu bar
    Gtk::MenuItem *menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
    menubar->append(*menuitem_file);
    Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);

    //         N E W   E M P O R I U M
    // (Owner) “Create a New Emporium” Append New to the File menu
    menuitem_new = Gtk::manage(new Gtk::MenuItem("_New Emporium", true));
    // menuitem_new->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_file_new_click));
    filemenu->append(*menuitem_new);

    //         O P E N   E M P O R I U M
    // (Owner) “Open an Emporium File” Append Open to the File menu
    menuitem_open = Gtk::manage(new Gtk::MenuItem("_Open", true));
    menuitem_open->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_file_open_click));
    filemenu->append(*menuitem_open);

    //         S A V E   E M P O R I U M
    // (Owner) “Save an Emporium File” Append Save to the File menu
    menuitem_save = Gtk::manage(new Gtk::MenuItem("_Save", true));
    menuitem_save->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_file_save_click));
    filemenu->append(*menuitem_save);

    //         E A S T E R   E G G
    // (TODO: Test Only) “Create a New Emporium” Append Easter Egg to the File menu
    menuitem_easteregg = Gtk::manage(new Gtk::MenuItem("_Easter Egg", true));
    menuitem_easteregg->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_easteregg_click));
    filemenu->append(*menuitem_easteregg);

    //         Q U I T
    // Append Quit to the File menu
    menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
    menuitem_quit->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_quit_click));
    filemenu->append(*menuitem_quit);

    //
    //     C R E A T E
    // Create a Create menu and add to the menu bar
    Gtk::MenuItem *menuitem_create = Gtk::manage(new Gtk::MenuItem("_Create", true));
    menubar->append(*menuitem_create);
    Gtk::Menu *createmenu = Gtk::manage(new Gtk::Menu());
    menuitem_create->set_submenu(*createmenu);

    //         O R D E R
    // (All) “Create Delicious Ice Cream Treats” Append Order to the Create menu
    menuitem_order = Gtk::manage(new Gtk::MenuItem("_Order...", true));
    menuitem_order->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_create_order_click));
    createmenu->append(*menuitem_order);

    //         C U S T O M E R
    // (Server, Manager, Owner) “Create a New Customer” Append Customer to the Create menu
    menuitem_customer = Gtk::manage(new Gtk::MenuItem("_Customer...", true));
    menuitem_customer->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_create_customer_click));
    createmenu->append(*menuitem_customer);

    //         I T E M 
    // (Owner, Manager) “Create a New Container, Ice Cream Flavor, or Topping” Append Item to the Create menu
    menuitem_item = Gtk::manage(new Gtk::MenuItem("_Item...", true));
    menuitem_item->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_create_item_click));
    createmenu->append(*menuitem_item);

    //         S E R V E R
    // (Owner, Manager) “Add a New Employee” Append Server to the Create menu
    menuitem_server = Gtk::manage(new Gtk::MenuItem("_Server...", true));
    menuitem_server->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_create_server_click));
    createmenu->append(*menuitem_server);

    //
    //     P R O C E S S
    // Create a Process menu and add to the menu bar
    Gtk::MenuItem *menuitem_process = Gtk::manage(new Gtk::MenuItem("_Process", true));
    menubar->append(*menuitem_process);
    Gtk::Menu *processmenu = Gtk::manage(new Gtk::Menu());
    menuitem_process->set_submenu(*processmenu);

    //         F I L L   O R D E R
    // (Server) “_Fill Order..."
    menuitem_fill_order = Gtk::manage(new Gtk::MenuItem("_Fill Order", true));
    menuitem_fill_order->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_fill_order_click));
    processmenu->append(*menuitem_fill_order);

    //         P A Y
    // (All) “_Pay.."
    menuitem_pay_for_order = Gtk::manage(new Gtk::MenuItem("_Pay for Order", true));
    menuitem_pay_for_order->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_pay_for_order_click));
    processmenu->append(*menuitem_pay_for_order);

    //         C A N C E L   O R D E R
    // (Customer, Server) “_Fill Order...", true));
    menuitem_cancel_order = Gtk::manage(new Gtk::MenuItem("_Cancel Order", true));
    menuitem_cancel_order->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_cancel_order_click));
    processmenu->append(*menuitem_cancel_order);

    //     R E P O R T
    // Create a Report menu and add to the menu bar
    Gtk::MenuItem *menuitem_report = Gtk::manage(new Gtk::MenuItem("_Report", true));
    menubar->append(*menuitem_report);
    Gtk::Menu *reportmenu = Gtk::manage(new Gtk::Menu());
    menuitem_report->set_submenu(*reportmenu);

    //           R E C E I P T
    // Append Receipt to the Role menu
    Gtk::MenuItem *menuitem_receipt_report = Gtk::manage(new Gtk::MenuItem("_Receipt", true));
    menuitem_receipt_report->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_receipt_click));
    reportmenu->append(*menuitem_receipt_report);

    //           S E R V E R   P R E P
    // Append Server Prep to the Role menu
    Gtk::MenuItem *menuitem_server_prep_report = Gtk::manage(new Gtk::MenuItem("_Server Prep", true));
    menuitem_server_prep_report->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_server_prep_click));
    reportmenu->append(*menuitem_server_prep_report);

    //     R O L E
    // Create a Role menu and add to the menu bar
    Gtk::MenuItem *menuitem_role = Gtk::manage(new Gtk::MenuItem("Role", true));
    menubar->append(*menuitem_role);
    Gtk::Menu *rolemenu = Gtk::manage(new Gtk::Menu());
    menuitem_role->set_submenu(*rolemenu);

    //           A L L
    // Append All to the Role menu
    Gtk::MenuItem *menuitem_all_role = Gtk::manage(new Gtk::MenuItem("All", true));
    menuitem_all_role->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_all_click));
    rolemenu->append(*menuitem_all_role);

    //           O W N E R
    // Append Owner to the Role menu
    Gtk::MenuItem *menuitem_owner_role = Gtk::manage(new Gtk::MenuItem("Owner", true));
    menuitem_owner_role->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_owner_click));
    rolemenu->append(*menuitem_owner_role);

    //           M A N A G E R
    // Append Manager to the Role menu
    Gtk::MenuItem *menuitem_manager_role = Gtk::manage(new Gtk::MenuItem("Manager", true));
    menuitem_manager_role->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_manager_click));
    rolemenu->append(*menuitem_manager_role);

    //           S E R V E R
    // Append Manager to the Role menu
    Gtk::MenuItem *menuitem_server_role = Gtk::manage(new Gtk::MenuItem("Server", true));
    menuitem_server_role->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_server_click));
    rolemenu->append(*menuitem_server_role);

    //           C U S T O M E R
    // Append Customer to the Role menu
    Gtk::MenuItem *menuitem_customer_role = Gtk::manage(new Gtk::MenuItem("Customer", true));
    menuitem_customer_role->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_customer_click));
    rolemenu->append(*menuitem_customer_role);

    //     H E L P
    // Create a Help menu and add to the menu bar
    Gtk::MenuItem *menuitem_help = Gtk::manage(new Gtk::MenuItem("_Help", true));
    menubar->append(*menuitem_help);
    Gtk::Menu *helpmenu = Gtk::manage(new Gtk::Menu());
    menuitem_help->set_submenu(*helpmenu);

    //           A B O U T
    // Append About to the Help menu
    Gtk::MenuItem *menuitem_about = Gtk::manage(new Gtk::MenuItem("About", true));
    menuitem_about->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_about_click));
    helpmenu->append(*menuitem_about);

    // /////////////
    // T O O L B A R
    // Add a toolbar to the vertical box below the menu
    Gtk::Toolbar *toolbar = Gtk::manage(new Gtk::Toolbar);
    vbox->add(*toolbar);

    //     N E W   E M P O R I U M
    // Add a new emporium icon
    new_emporium_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::NEW));
    new_emporium_button->set_tooltip_markup("Create a New Emporium");
    //new_emporium_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_file_new_click));
    toolbar->append(*new_emporium_button);

    //     C R E A T E   O R D E R
    // Add a Create Order icon
    Gtk::Image *create_order_button_image = Gtk::manage(new Gtk::Image("new_order.png"));
    create_order_button = Gtk::manage(new Gtk::ToolButton(*create_order_button_image));
    create_order_button->set_tooltip_markup("Create a new order");
    create_order_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_create_order_click));
    toolbar->append(*create_order_button);

    //     C R E A T E   C R E A T E   I T E M
    // Add a Create Item icon
    Gtk::Image *create_item_button_image = Gtk::manage(new Gtk::Image("create_item.png"));
    create_item_button = Gtk::manage(new Gtk::ToolButton(*create_item_button_image));
    create_item_button->set_tooltip_markup("Create a new item");
    create_item_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_create_item_click));
    toolbar->append(*create_item_button);

    //     Q U I T
    // Add a icon for quitting
    Gtk::ToolButton *quit_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::QUIT));
    quit_button->set_tooltip_markup("Exit MICE");
    quit_button->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_quit_click));
    Gtk::SeparatorToolItem *sep = Gtk::manage(new Gtk::SeparatorToolItem());
    sep->set_expand(true);  // The expanding sep forces the Quit button to the right
    toolbar->append(*sep);
    toolbar->append(*quit_button);

    // Make the box and everything in it visible
    vbox->show_all();

    // Start with a default emporium
    _emp = new Mice::Emporium{"Default"};
    set_title("Mav's Ice Cream Emporium");
}

Mainwin::~Mainwin() { }

void Mainwin::on_quit_click() {
    hide();
}

// Set sensitivities based on role

void Mainwin::on_all_click() {
    menuitem_new->set_sensitive(true);
    menuitem_open->set_sensitive(true);
    menuitem_save->set_sensitive(true);
    menuitem_easteregg->set_sensitive(true);
    menuitem_quit->set_sensitive(true);
    menuitem_order->set_sensitive(true);
    menuitem_customer->set_sensitive(true);
    menuitem_item->set_sensitive(true);
    menuitem_server->set_sensitive(true);
    menuitem_fill_order->set_sensitive(true);
    menuitem_pay_for_order->set_sensitive(true);
    menuitem_cancel_order->set_sensitive(true);

    new_emporium_button->set_sensitive(menuitem_new->get_sensitive());
    create_order_button->set_sensitive(menuitem_order->get_sensitive());
    create_item_button->set_sensitive(menuitem_item->get_sensitive());
}

void Mainwin::on_owner_click() {
    menuitem_new->set_sensitive(true);
    menuitem_open->set_sensitive(true);
    menuitem_save->set_sensitive(true);
    menuitem_easteregg->set_sensitive(true);
    menuitem_quit->set_sensitive(true);
    menuitem_order->set_sensitive(true);
    menuitem_customer->set_sensitive(true);
    menuitem_item->set_sensitive(true);
    menuitem_server->set_sensitive(true);
    menuitem_fill_order->set_sensitive(true);
    menuitem_pay_for_order->set_sensitive(true);
    menuitem_cancel_order->set_sensitive(true);

    new_emporium_button->set_sensitive(menuitem_new->get_sensitive());
    create_order_button->set_sensitive(menuitem_order->get_sensitive());
    create_item_button->set_sensitive(menuitem_item->get_sensitive());
}

void Mainwin::on_manager_click() {
    menuitem_new->set_sensitive(false);
    menuitem_open->set_sensitive(true);
    menuitem_save->set_sensitive(true);
    menuitem_easteregg->set_sensitive(true);
    menuitem_quit->set_sensitive(true);
    menuitem_order->set_sensitive(true);
    menuitem_customer->set_sensitive(true);
    menuitem_item->set_sensitive(true);
    menuitem_server->set_sensitive(true);
    menuitem_fill_order->set_sensitive(true);
    menuitem_pay_for_order->set_sensitive(true);
    menuitem_cancel_order->set_sensitive(true);

    new_emporium_button->set_sensitive(menuitem_new->get_sensitive());
    create_order_button->set_sensitive(menuitem_order->get_sensitive());
    create_item_button->set_sensitive(menuitem_item->get_sensitive());
}

void Mainwin::on_server_click() {
    menuitem_new->set_sensitive(false);
    menuitem_open->set_sensitive(false);
    menuitem_save->set_sensitive(false);
    menuitem_easteregg->set_sensitive(false);
    menuitem_quit->set_sensitive(true);
    menuitem_order->set_sensitive(true);
    menuitem_customer->set_sensitive(true);
    menuitem_item->set_sensitive(false);
    menuitem_server->set_sensitive(false);
    menuitem_fill_order->set_sensitive(true);
    menuitem_pay_for_order->set_sensitive(true);
    menuitem_cancel_order->set_sensitive(true);

    new_emporium_button->set_sensitive(menuitem_new->get_sensitive());
    create_order_button->set_sensitive(menuitem_order->get_sensitive());
    create_item_button->set_sensitive(menuitem_item->get_sensitive());
}

void Mainwin::on_customer_click() {
    menuitem_new->set_sensitive(false);
    menuitem_open->set_sensitive(false);
    menuitem_save->set_sensitive(false);
    menuitem_easteregg->set_sensitive(false);
    menuitem_quit->set_sensitive(false);
    menuitem_order->set_sensitive(true);
    menuitem_customer->set_sensitive(false);
    menuitem_item->set_sensitive(false);
    menuitem_server->set_sensitive(false);
    menuitem_fill_order->set_sensitive(false);
    menuitem_pay_for_order->set_sensitive(false);
    menuitem_cancel_order->set_sensitive(true);

    new_emporium_button->set_sensitive(menuitem_new->get_sensitive());
    create_order_button->set_sensitive(menuitem_order->get_sensitive());
    create_item_button->set_sensitive(menuitem_item->get_sensitive());
}

