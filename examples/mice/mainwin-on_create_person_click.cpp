#include "mainwin.h"
#include <exception>
#include <stdexcept>
#include <regex>

void Mainwin::on_create_server_click() {
    on_create_person_click("Server");
}

void Mainwin::on_create_customer_click() {
    on_create_person_click("Customer");
}

void Mainwin::on_create_person_click(std::string role) {

    const int WIDTH = 15;

    Gtk::Dialog dialog{"Create " + role, *this};

    // Name 
    Gtk::HBox b_name;

    Gtk::Label l_name{"Name:"};
    l_name.set_width_chars(WIDTH);
    b_name.pack_start(l_name, Gtk::PACK_SHRINK);

    Gtk::Entry e_name;
    e_name.set_max_length(WIDTH*4);
    b_name.pack_start(e_name, Gtk::PACK_SHRINK);
    dialog.get_vbox()->pack_start(b_name, Gtk::PACK_SHRINK);

    // ID
    Gtk::HBox b_id;

    Gtk::Label l_id{"ID:"};
    l_id.set_width_chars(WIDTH);
    b_id.pack_start(l_id, Gtk::PACK_SHRINK);

    Gtk::Entry e_id;
    e_id.set_max_length(WIDTH*4);
    b_id.pack_start(e_id, Gtk::PACK_SHRINK);
    dialog.get_vbox()->pack_start(b_id, Gtk::PACK_SHRINK);

    // Phone
    Gtk::HBox b_phone;

    Gtk::Label l_phone{"Phone:"};
    l_phone.set_width_chars(WIDTH);
    b_phone.pack_start(l_phone, Gtk::PACK_SHRINK);

    Gtk::Entry e_phone;
    e_phone.set_max_length(WIDTH*4);
    b_phone.pack_start(e_phone, Gtk::PACK_SHRINK);
    dialog.get_vbox()->pack_start(b_phone, Gtk::PACK_SHRINK);

    // Salary (Server only)
    Gtk::HBox b_salary;

    Gtk::Label l_salary{"Hourly Wage:"};
    l_salary.set_width_chars(WIDTH);
    b_salary.pack_start(l_salary, Gtk::PACK_SHRINK);

    Gtk::Entry e_salary;
    e_salary.set_max_length(WIDTH*4);
    b_salary.pack_start(e_salary, Gtk::PACK_SHRINK);
    if (role == "Server") {
        dialog.get_vbox()->pack_start(b_salary, Gtk::PACK_SHRINK);
    }

    // Show dialog
    dialog.add_button("Cancel", 0);
    dialog.add_button("OK", 1);
    dialog.show_all();

    double d_salary;
    bool valid_data = false;

    while(!valid_data) {
        if (dialog.run() != 1) {
            dialog.close();
            return;
        }

        // Data validation
        valid_data = true;

        if (e_name.get_text().length() == 0) {
            e_name.set_text("*** name is required ***");
            valid_data = false;
        }

        if (e_id.get_text().length() == 0) {
            e_id.set_text("*** id is required ***");
            valid_data = false;
        }

        if (e_phone.get_text().length() == 0) {
            e_phone.set_text("*** phone is required ***");
            valid_data = false;
        }

        // REGEX - Supports US phone numbers only, with optional area code
        // delimited with parentheses, a dash, or no delimeters at all, e.g.
        // (817) 555-1212, 817-555-1212, 8175551212, or 555-1212
        std::regex r_phone{"(\\(?\\d{3}\\)?\\s*\\-?)?\\d{3}\\-?\\d{4}"}; 
        std::string phone = e_phone.get_text(); // because g++ complains otherwise
        if (!std::regex_match(phone, r_phone)) {
            e_phone.set_text("*** Invalid: " + e_phone.get_text());
            valid_data = false;
        }

        if (role == "Server") {
            try {
                d_salary = std::stod(e_salary.get_text());
            } catch(std::exception e) {
                e_salary.set_text("*** invalid salary ***");
                valid_data = false;
            }
        }

        for (int s=0; s < _emp->num_servers(); ++s) {
            if (_emp->server(s).name() == e_name.get_text()) {
                e_name.set_text("*** duplicate name ***");
                valid_data = false;
            }
            if (_emp->server(s).id() == e_id.get_text()) {
                e_id.set_text("*** duplicate id ***");
                valid_data = false;
            }
        }
    }
        
    // Instance person
    if (role == "Server") {
        Mice::Server s{e_name.get_text(), e_id.get_text(), e_phone.get_text(), d_salary};
        _emp->add_server(s);
    } else if (role == "Customer") {
        Mice::Customer c{e_name.get_text(), e_id.get_text(), e_phone.get_text()};
        _emp->add_customer(c);
    }
    
    dialog.close();
}
