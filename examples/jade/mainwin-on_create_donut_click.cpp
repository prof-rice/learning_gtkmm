#include "mainwin.h"
#include "donut.h"

// //////////////////////////
// Create a new donut product

void Mainwin::on_create_donut_click() { 
    std::string name;
    double price, cost;

    Gtk::Dialog *dialog = new Gtk::Dialog{"Create a Donut", *this};

    // Name
    Gtk::HBox b_name;

    Gtk::Label l_name{"Name:"};
    l_name.set_width_chars(15);
    b_name.pack_start(l_name, Gtk::PACK_SHRINK);

    Gtk::Entry e_name;
    e_name.set_max_length(50);
    b_name.pack_start(e_name, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_name, Gtk::PACK_SHRINK);

    // Price
    Gtk::HBox b_price;

    Gtk::Label l_price{"Price:"};
    l_price.set_width_chars(15);
    b_price.pack_start(l_price, Gtk::PACK_SHRINK);

    Gtk::Entry e_price;
    e_price.set_max_length(50);
    b_price.pack_start(e_price, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_price, Gtk::PACK_SHRINK);

    // Cost
    Gtk::HBox b_cost;

    Gtk::Label l_cost{"Cost:"};
    l_cost.set_width_chars(15);
    b_cost.pack_start(l_cost, Gtk::PACK_SHRINK);

    Gtk::Entry e_cost;
    e_cost.set_max_length(50);
    b_cost.pack_start(e_cost, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_cost, Gtk::PACK_SHRINK);

    // Frosting
    Gtk::HBox b_frosting;

    Gtk::Label l_frosting{"Frosting:"};
    l_frosting.set_width_chars(15);
    b_frosting.pack_start(l_frosting, Gtk::PACK_SHRINK);

    Gtk::ComboBoxText c_frosting;
    c_frosting.set_size_request(160);
    for (auto s: frosting_to_string) c_frosting.append(s);
    b_frosting.pack_start(c_frosting, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_frosting, Gtk::PACK_SHRINK);

    // Filling
    Gtk::HBox b_filling;

    Gtk::Label l_filling{"Filling:"};
    l_filling.set_width_chars(15);
    b_filling.pack_start(l_filling, Gtk::PACK_SHRINK);

    Gtk::ComboBoxText c_filling;
    c_filling.set_size_request(160);
    for (auto s: filling_to_string) c_filling.append(s);
    b_filling.pack_start(c_filling, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_filling, Gtk::PACK_SHRINK);

    // Sprinkles
    Gtk::CheckButton c_sprinkles{"Add sprinkles"};
    dialog->get_vbox()->pack_start(c_sprinkles, Gtk::PACK_SHRINK);

    // Show dialog
    dialog->add_button("Cancel", 0);
    dialog->add_button("Create", 1);
    dialog->show_all();

    int result; // of the dialog (1 = OK)
    bool fail = true;  // set to true if any data is invalid

    while (fail) {
        fail = false;  // optimist!
        result = dialog->run();
        if (result != 1) {delete dialog; return;}
        try {
            price = std::stod(e_price.get_text());
        } catch(std::exception e) {
            e_price.set_text("### Invalid ###");
            fail = true;
        }
        try {
            cost = std::stod(e_cost.get_text());
        } catch(std::exception e) {
            e_cost.set_text("### Invalid ###");
            fail = true;
        }
        name = e_name.get_text();
        if (name.size() == 0) {
            e_name.set_text("### Invalid ###");
            fail = true;
        }
    }

    Frosting frosting = (Frosting)(c_frosting.get_active_row_number());
    if (frosting < 0 || frosting >= frosting_to_string.size()) frosting = Unfrosted;

    Filling filling = (Filling)(c_filling.get_active_row_number());
    if (filling < 0 || filling >= filling_to_string.size()) filling = Unfilled;

    bool sprinkles = (c_sprinkles.get_active() && (frosting != Unfrosted));

    Donut* d = new Donut{name, price, cost, frosting, sprinkles, filling};
    _store.add_product(d);
    msg->set_text("New donut product \"" + name + "\" created");

    delete dialog;
}
