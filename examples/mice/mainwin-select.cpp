#include "mainwin.h"
#include <exception>
#include <stdexcept>

int Mainwin::select_container() {
    if (_emp->num_containers() == 0) {
        Gtk::MessageDialog dialog{*this, "At least 1 container must be created first"};
        dialog.run();
        dialog.close();
        return -1;
    }
    if (_emp->num_containers() == 1) return 0;
    std::vector<std::string> names;
    for (int c=0; c < _emp->num_containers(); ++c) {
        names.push_back(_emp->container(c).name());
    }
    return select_from_vector(names, "Container");
}

int Mainwin::select_scoop() {
    if (_emp->num_scoops() == 0) {
        Gtk::MessageDialog dialog{*this, "At least 1 scoop must be created first"};
        dialog.run();
        dialog.close();
        return -1;
    }
    std::vector<std::string> names;
    for (int s=0; s < _emp->num_scoops(); ++s) {
        names.push_back(_emp->scoop(s).name());
    }
    return select_from_vector(names, "Scoop");
}

int Mainwin::select_topping() {
    if (_emp->num_toppings() == 0) {
        Gtk::MessageDialog dialog{*this, "At least 1 topping must be created first"};
        dialog.run();
        dialog.close();
        return -1;
    }
    std::vector<std::string> names;
    for (int t=0; t < _emp->num_toppings(); ++t) {
        names.push_back(_emp->topping(t).name());
    }
    return select_from_vector(names, "Topping");
}

int Mainwin::select_order() {
    if (_emp->num_orders() == 0) return -1;
    std::vector<std::string> names;
    for (int t=0; t < _emp->num_orders(); ++t) 
        names.push_back("Order " + std::to_string(_emp->order(t).id()));
    return select_from_vector(names, "Order");
}

int Mainwin::select_order(Mice::Order_state state) {
    std::vector<std::string> names;
    std::vector<int> order_ids;
    for (int t=0; t < _emp->num_orders(); ++t) {
        if (_emp->order(t).state() == state) {
            names.push_back("Order " + std::to_string(_emp->order(t).id()));
            order_ids.push_back(t);
        }
    }
    if (names.size() == 0) {
        Gtk::MessageDialog dialog{*this, "No orders qualify for this action"};
        dialog.run();
        dialog.close();
        return -1;
    }
    int selection = select_from_vector(names, "Order");
    return (selection >= 0) ? order_ids[selection] : selection;
}

int Mainwin::select_customer() {
    if (_emp->num_customers() == 0) on_create_customer_click();
    if (_emp->num_customers() == 0) return -1;
    std::vector<std::string> names;
    for (int c=0; c < _emp->num_customers(); ++c) {
        names.push_back(_emp->customer(c).name());
    }
    return select_from_vector(names, "Customer");
}

int Mainwin::select_server() {
    if (_emp->num_servers() == 0) on_create_server_click();
    if (_emp->num_servers() == 0) return -1;
    std::vector<std::string> names;
    for (int s=0; s < _emp->num_servers(); ++s) {
        names.push_back(_emp->server(s).name());
    }
    return select_from_vector(names, "Server");
}

int Mainwin::select_from_vector(std::vector<std::string> names, std::string title) {

    Gtk::Dialog dialog_index{"Select " + title, *this};
    const int WIDTH = 15;

    // Container
    Gtk::HBox b_index;

    Gtk::Label l_index{title + ":"};
    l_index.set_width_chars(WIDTH);
    b_index.pack_start(l_index, Gtk::PACK_SHRINK);

    // Create dropdown list
    Gtk::ComboBoxText c_index;
    c_index.set_size_request(WIDTH*10);
    for (std::string s : names) c_index.append(s);
    b_index.pack_start(c_index, Gtk::PACK_SHRINK);
    dialog_index.get_vbox()->pack_start(b_index, Gtk::PACK_SHRINK);

    // Show dialog_index
    dialog_index.add_button("Cancel", 0);
    dialog_index.add_button("OK", 1);
    dialog_index.show_all();
    if (dialog_index.run() != 1) return -1;

    int index = c_index.get_active_row_number();

    dialog_index.close();

    return index;
}
