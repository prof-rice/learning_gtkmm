#include "main_window.h"
#include "dialogs.h"
#include <sstream>

Main_window::Main_window() {
    Dialogs::set_window(this);

    // /////////////////
    // G U I   S E T U P
    // /////////////////

    set_default_size(640, 400);
    set_title("MavMart");

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

    //         N E W   S T O R E
    // Append New to the File menu
    Gtk::MenuItem *menuitem_new = Gtk::manage(new Gtk::MenuItem("_New", true));
    menuitem_new->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_new_click));
    filemenu->append(*menuitem_new);

    //         O P E N   S T O R E
    // Append Open to the File menu
    Gtk::MenuItem *menuitem_open = Gtk::manage(new Gtk::MenuItem("_Open", true));
    menuitem_open->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_open_click));
    filemenu->append(*menuitem_open);

    //         S A V E   S T O R E
    // Append save to the File menu
    Gtk::MenuItem *menuitem_save = Gtk::manage(new Gtk::MenuItem("_Save", true));
    menuitem_save->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_save_click));
    filemenu->append(*menuitem_save);

    //         S A V E  A S  S T O R E
    // Append save as to the File menu
    Gtk::MenuItem *menuitem_save_as = Gtk::manage(new Gtk::MenuItem("Save _As", true));
    menuitem_save_as->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_save_as_click));
    filemenu->append(*menuitem_save_as);

    //         Q U I T
    // Append Quit to the File menu
    Gtk::MenuItem *menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
    menuitem_quit->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_quit_click));
    filemenu->append(*menuitem_quit);


    //     P R O D U C T
    // Create a Product menu and add to the menu bar
    Gtk::MenuItem *menuitem_product = Gtk::manage(new Gtk::MenuItem("_Product", true));
    menubar->append(*menuitem_product);
    Gtk::Menu *productmenu = Gtk::manage(new Gtk::Menu());
    menuitem_product->set_submenu(*productmenu);

    //         A D D   P R O D U C T
    // Append New to the File menu
    Gtk::MenuItem *_menuitem_add_product = Gtk::manage(new Gtk::MenuItem("_Add", true));
    _menuitem_add_product->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_add_product_click));
    productmenu->append(*_menuitem_add_product);

    //         L I S T   P R O D U C T S
    // Append List Products to the Product menu
    Gtk::MenuItem *_menuitem_list_products = Gtk::manage(new Gtk::MenuItem("_List", true));
    _menuitem_list_products->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_list_products_click));
    productmenu->append(*_menuitem_list_products);

    //     O R D E R
    // Create a order menu and add to the menu bar
    Gtk::MenuItem *menuitem_order = Gtk::manage(new Gtk::MenuItem("_Order", true));
    menubar->append(*menuitem_order);
    Gtk::Menu *ordermenu = Gtk::manage(new Gtk::Menu());
    menuitem_order->set_submenu(*ordermenu);

    //         A D D   O R D E R
    // Append New to the File menu
    Gtk::MenuItem *_menuitem_add_order = Gtk::manage(new Gtk::MenuItem("_Add", true));
    _menuitem_add_order->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_add_order_click));
    ordermenu->append(*_menuitem_add_order);

    //         L I S T   O R D E R S
    // Append List orders to the order menu
    Gtk::MenuItem *_menuitem_list_orders = Gtk::manage(new Gtk::MenuItem("_List", true));
    _menuitem_list_orders->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_list_orders_click));
    ordermenu->append(*_menuitem_list_orders);

    //     H E L P
    // Create a Help menu and add to the menu bar
    Gtk::MenuItem *menuitem_help = Gtk::manage(new Gtk::MenuItem("_Help", true));
    menubar->append(*menuitem_help);
    Gtk::Menu *helpmenu = Gtk::manage(new Gtk::Menu());
    menuitem_help->set_submenu(*helpmenu);

    //           H E L P
    // Append Help to the Help menu
    Gtk::MenuItem *menuitem_helps = Gtk::manage(new Gtk::MenuItem("_Help", true));
    menuitem_helps->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_help_click));
    helpmenu->append(*menuitem_helps);

    //           T E S T   (Easter Egg)
    // Append test to the Help menu
    Gtk::MenuItem *menuitem_test = Gtk::manage(new Gtk::MenuItem("_Test", true));
    menuitem_test->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_test_click));
    helpmenu->append(*menuitem_test);

    //           A B O U T
    // Append About to the Help menu
    Gtk::MenuItem *menuitem_about = Gtk::manage(new Gtk::MenuItem("About", true));
    menuitem_about->signal_activate().connect(sigc::mem_fun(*this, &Main_window::on_about_click));
    helpmenu->append(*menuitem_about);

    // /////////////
    // T O O L B A R
    // Add a toolbar to the vertical box below the menu
    Gtk::Toolbar *toolbar = Gtk::manage(new Gtk::Toolbar);
    vbox->add(*toolbar);

    //     A D D   P R O D U C T
    // Add a icon for adding a product
    Gtk::Image* button_add_product_image = Gtk::manage(new Gtk::Image{"add_product.png"});
    Gtk::ToolButton* button_add_product = Gtk::manage(new Gtk::ToolButton(*button_add_product_image));
    button_add_product->set_tooltip_markup("Add a new product");
    button_add_product->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_add_product_click));
    toolbar->append(*button_add_product);

    //     L I S T   P R O D U C T S
    // Add a icon for listing all products
    Gtk::Image* button_list_products_image = Gtk::manage(new Gtk::Image{"list_all_products.png"});
    Gtk::ToolButton* button_list_products = Gtk::manage(new Gtk::ToolButton(*button_list_products_image));
    button_list_products->set_tooltip_markup("List all products");
    button_list_products->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_list_products_click));
    toolbar->append(*button_list_products);

    //     A D D   O R D E R
    // Add a icon for adding a order
    Gtk::Image* button_add_order_image = Gtk::manage(new Gtk::Image{"add_order.png"});
    Gtk::ToolButton* button_add_order = Gtk::manage(new Gtk::ToolButton(*button_add_order_image));
    button_add_order->set_tooltip_markup("Add a new order");
    button_add_order->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_add_order_click));
    toolbar->append(*button_add_order);

    //     L I S T   O R D E R S
    // Add a icon for listing all orders
    Gtk::Image* button_list_orders_image = Gtk::manage(new Gtk::Image{"list_all_orders.png"});
    Gtk::ToolButton* button_list_orders = Gtk::manage(new Gtk::ToolButton(*button_list_orders_image));
    button_list_orders->set_tooltip_markup("List all orders");
    button_list_orders->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_list_orders_click));
    toolbar->append(*button_list_orders);

    //     D I S P L A Y   S E L E C T O R
    // Add a toggle button to switch main window between products and orders
    Gtk::Image *display_selector_image = Gtk::manage(new Gtk::Image{"display_selector.png"});
    Gtk::ToggleToolButton* display_selector = Gtk::manage(new Gtk::ToggleToolButton(*display_selector_image));
    display_selector->set_tooltip_markup("Enable for Orders, Disable for Products");
    // display_selector->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_display_selector_click));
    Gtk::SeparatorToolItem *sep1 = Gtk::manage(new Gtk::SeparatorToolItem());
    toolbar->append(*sep1);
    toolbar->append(*display_selector);

    //     H E L P
    // Add a icon for helpting
    Gtk::ToolButton *help_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::HELP));
    help_button->set_tooltip_markup("Help");
    help_button->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_help_click));
    Gtk::SeparatorToolItem *sep2 = Gtk::manage(new Gtk::SeparatorToolItem());
    sep2->set_expand(true);  // The expanding sep forces the help button to the right
    toolbar->append(*sep2);
    toolbar->append(*help_button);

    //     Q U I T
    // Add a icon for quitting
    Gtk::ToolButton *quit_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::QUIT));
    quit_button->set_tooltip_markup("Exit");
    quit_button->signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_quit_click));
    Gtk::SeparatorToolItem *sep3 = Gtk::manage(new Gtk::SeparatorToolItem());
    toolbar->append(*sep3);
    toolbar->append(*quit_button);

    // ///////////////////////
    // D A T A   D I S P L A Y
    // Provide a scrolling text entry box to show the remaining sticks
    data = Gtk::manage(new Gtk::Label());
    data->set_use_markup(true);
    data->set_alignment(Gtk::ALIGN_CENTER, Gtk::ALIGN_START);
    Gtk::ScrolledWindow* scroller = Gtk::manage(new Gtk::ScrolledWindow);
    scroller->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_ALWAYS);
    scroller->add(*data);
    data->set_hexpand(true);
    data->set_vexpand(true);
    vbox->add(*scroller);
    
    // ///////////////////////////////////
    // S T A T U S   B A R   D I S P L A Y
    // Provide a status bar for game messages
    msg = Gtk::manage(new Gtk::Label());
    msg->set_hexpand(true);
    vbox->add(*msg);

    // Make the box and everything in it visible
    vbox->show_all();

    // Start a new game
    on_new_click();
}

Main_window::~Main_window() { }

// /////////////////
// C A L L B A C K S
// /////////////////

void Main_window::on_new_click() {
    msg->set_text("Creating new store");
    controller = new Controller{this};
    msg->set_text("New store created");
    set_data();
}
void Main_window::on_open_click() {
    msg->set_text("");
    controller->load();
    msg->set_text("Current file is " + controller->filename());
    set_data();
}           
void Main_window::on_save_click() {
    msg->set_text("Saving " + controller->filename());
    controller->save(false);
    msg->set_text(controller->filename() + "saved");
}           
void Main_window::on_save_as_click() {
    controller->save();
    msg->set_text(controller->filename() + "saved");
}
void Main_window::on_quit_click() {
    hide();
}        
void Main_window::on_add_product_click() {
    msg->set_text("");
    controller->add_product();
    msg->set_text(std::to_string(controller->num_products()) + " products, " 
                + std::to_string(controller->num_orders())   + " orders");
    set_data();
}    
void Main_window::on_list_products_click() {
    msg->set_text(std::to_string(controller->num_products()) + " products, " 
                + std::to_string(controller->num_orders())   + " orders");
    controller->list_all_products();
}  
void Main_window::on_add_order_click() {
    msg->set_text("");
    controller->add_order();
    msg->set_text(std::to_string(controller->num_products()) + " products, " 
                + std::to_string(controller->num_orders())   + " orders");
    set_data();
}      
void Main_window::on_list_orders_click() {
    msg->set_text(std::to_string(controller->num_products()) + " products, " 
                + std::to_string(controller->num_orders())   + " orders");
    controller->list_all_orders();
}    
void Main_window::on_help_click() {
    msg->set_text("");
    controller->help();
}
void Main_window::on_test_click() {
    controller->easter_egg();
    msg->set_text("9 products added");
    set_data();
}
void Main_window::on_about_click() {
    msg->set_text("");
    Glib::ustring s = "<span size='24000' weight='bold'>MavMart</span>\n<span size='large'>Copyright 2019 by George F. Rice</span>\n<span size='small'>Licensed under Creative Commons Attribution 4.0 International</span>";
    Gtk::MessageDialog dlg(*this, s, true, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
    dlg.run();
}

// /////////////////
// U T I L I T I E S
// /////////////////
void Main_window::set_data() {
    data->set_markup("<span font_desc='monospace 14' weight='bold'>" + controller->all_products() + "</span>");
    //data->set_text("<span font=\"serif,monospace bold italic condensed 16\">" + controller->all_products() + "</span>");

}

