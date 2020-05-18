#include "controller.h"
#include "dialogs.h"
#include <gtkmm.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>

Controller::Controller() : Controller(Rental_site{}) { }
Controller::Controller(Rental_site rental_site) : _rental_site{rental_site}, _view{View{_rental_site}} { }

int Controller::get_int(std::string prompt, std::string title) {
    int result;
    while(true) {
        std::string s = Dialogs::input(prompt, title);

        if (s.empty()) throw std::runtime_error{"Null input"};
        if (s == "CANCEL") throw std::runtime_error{Controller::CANCEL_X};
        std::istringstream ist{s};
        if (ist >> result) break;
        Dialogs::message("### Invalid input", "Error");
    }
    return result;
}
        
void Controller::cli() {
    int cmd;
    while(true) {
        try {
            cmd = get_int(_view.main_menu(), "Main Menu");
            if (cmd == 0) break;
            execute_cmd(cmd);
        } catch (std::runtime_error& e) {
            if (e.what() == Controller::CANCEL_X) break; // CANCEL was clicked
        }
    }
}

std::string Controller::vehicle_menu(bool rented, bool unrented) {
    std::ostringstream ost;
    for (std::string vehicle : _view.list_of_vehicles(rented, unrented))
        ost << vehicle << std::endl;
    return ost.str();
}

std::vector<std::vector<std::string>> Controller::vehicles() {
    return _rental_site.vehicles_to_strings();
}

std::string Controller::renter_menu() {
    std::ostringstream ost;
    for (std::string renter : _view.list_of_renters())
        ost << renter << std::endl;
    return ost.str();
}

void Controller::execute_cmd(int cmd) {
    switch(cmd) {
        case 1: { // Add vehicle
            try {
                std::string make, model;
                int year, body_style;

                Gtk::Dialog *dialog = new Gtk::Dialog();
                dialog->set_title("Create Vehicle");

                // Model Year
                Gtk::HBox b_year;

                Gtk::Label l_year{"Year:"};
                l_year.set_width_chars(15);
                b_year.pack_start(l_year, Gtk::PACK_SHRINK);

                Gtk::Entry e_year;
                e_year.set_max_length(50);
                b_year.pack_start(e_year, Gtk::PACK_SHRINK);
                dialog->get_vbox()->pack_start(b_year, Gtk::PACK_SHRINK);

                // Make
                Gtk::HBox b_make;

                Gtk::Label l_make{"Make:"};
                l_make.set_width_chars(15);
                b_make.pack_start(l_make, Gtk::PACK_SHRINK);

                Gtk::Entry e_make;
                e_make.set_max_length(50);
                b_make.pack_start(e_make, Gtk::PACK_SHRINK);
                dialog->get_vbox()->pack_start(b_make, Gtk::PACK_SHRINK);

                // Model
                Gtk::HBox b_model;

                Gtk::Label l_model{"Model:"};
                l_model.set_width_chars(15);
                b_model.pack_start(l_model, Gtk::PACK_SHRINK);

                Gtk::Entry e_model;
                e_model.set_max_length(50);
                b_model.pack_start(e_model, Gtk::PACK_SHRINK);
                dialog->get_vbox()->pack_start(b_model, Gtk::PACK_SHRINK);

                // Body style
                Gtk::HBox b_body_style;

                Gtk::Label l_body_style{"Body style:"};
                l_body_style.set_width_chars(15);
                b_body_style.pack_start(l_body_style, Gtk::PACK_SHRINK);

                Gtk::ComboBoxText c_body_style;
                c_body_style.set_size_request(160);
                c_body_style.append("Sedan");
                c_body_style.append("Hatchback");
                c_body_style.append("Minivan");
                c_body_style.append("Truck");
                c_body_style.append("Crossover");
                c_body_style.append("SUV");
                b_body_style.pack_start(c_body_style, Gtk::PACK_SHRINK);
                dialog->get_vbox()->pack_start(b_body_style, Gtk::PACK_SHRINK);

                // Show dialog
                dialog->add_button("Cancel", 0);
                dialog->add_button("OK", 1);
                dialog->show_all();
                int result = Dialogs::run_dialog(dialog);

                dialog->close();
                //while (Gtk::Main::events_pending())  Gtk::Main::iteration();

                try {
                    if (result == 1) {
                        make = e_make.get_text();
                        model = e_model.get_text();
                        year = std::stoi(e_year.get_text());
                        body_style = c_body_style.get_active_row_number();

                        _rental_site.add_vehicle(Vehicle{year, make, model, (Body_style)body_style});
                    }
                } catch (std::exception e) {
                   Dialogs::message("Unable to create new vehicle", "ERROR");
                }
            } catch(std::runtime_error e) {
                break;
            }

            break;
        }
        case 2: { // List all vehicles
            Dialogs::message(vehicle_menu(), "All Vehicles");
            break;
        }
        case 3: { // Rent a vehicle
            int vehicle;
            int renter;
            try {
                vehicle = get_int(vehicle_menu(false, true), "Select a Vehicle");
                renter = get_int(renter_menu(), "Select a Renter");
            } catch(std::runtime_error e) {
                break;
            }

            try {
                _rental_site.rent_vehicle(vehicle, renter);
            } catch(std::runtime_error e) {
                Dialogs::message("### That vehicle is already rented ###", "ERROR");
            }
            break;
        }
        case 4: { // Return a vehicle
            int vehicle;
            try {
                vehicle = get_int(vehicle_menu(true, false), "Select a Vehicle"); // list only rented vehicles
            } catch(std::runtime_error e) {
                break;
            }

            try {
               _rental_site.return_vehicle(vehicle);
            } catch(std::runtime_error e) {
                Dialogs::message("### That vehicle is not rented ###", "ERROR");
            }
            break;
        }
        case 5: { // Add renter
            std::string name = Dialogs::input("Renter's name? ", "Add Renter");
            std::string drivers_license = Dialogs::input("Renter's driver's license?", "Add Renter");
            std::string phone_number = Dialogs::input("Renter's phone number? ", "Add Renter");
            _rental_site.add_renter(Renter{name, drivers_license, phone_number});
            break;
        }
        case 6: { // List all renters
            Dialogs::message(renter_menu(), "All Renters");
            break;
        }
        case 17: { // Save
            std::ofstream ofs{_filename};
            if (ofs) _rental_site.save(ofs);
            else Dialogs::message("####Unable to save to " + _filename, "ERROR");
            break;
        }
        case 7: { // Save As
           Gtk::FileChooserDialog dialog("Please choose a file",
                  Gtk::FileChooserAction::FILE_CHOOSER_ACTION_SAVE);
            auto filter_rvms = Gtk::FileFilter::create();
            filter_rvms->set_name("RVMS files");
            filter_rvms->add_pattern("*.rvms");
            dialog.add_filter(filter_rvms);
 
            auto filter_any = Gtk::FileFilter::create();
            filter_any->set_name("Any files");
            filter_any->add_pattern("*");
            dialog.add_filter(filter_any);

            dialog.set_filename("untitled.rvms");

            dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
            dialog.add_button("_Save", Gtk::RESPONSE_OK);

            int result = Dialogs::run_dialog(&dialog);

            if (result == Gtk::RESPONSE_OK) {
                std::ofstream ofs{dialog.get_filename()};
                if (ofs) {
                    _rental_site.save(ofs);
                    _filename = dialog.get_filename();
                } else {
                    Dialogs::message("####Unable to save to " + dialog.get_filename(), "ERROR");
                }
            }
            break;
        }
        case 18: { // Load empty rental site
            _rental_site = Rental_site{};
            _filename = "untitled.rvms";
            break;
        }
        case 8: { // Load
            Gtk::FileChooserDialog dialog("Please choose a file",
            Gtk::FileChooserAction::FILE_CHOOSER_ACTION_OPEN);

            auto filter_rvms = Gtk::FileFilter::create();
            filter_rvms->set_name("RVMS files");
            filter_rvms->add_pattern("*.rvms");
            dialog.add_filter(filter_rvms);
 
            auto filter_text = Gtk::FileFilter::create();
            filter_text->set_name("Text files");
            filter_text->add_mime_type("text/plain");
            dialog.add_filter(filter_text);

            auto filter_any = Gtk::FileFilter::create();
            filter_any->set_name("Any files");
            filter_any->add_pattern("*");
            dialog.add_filter(filter_any);

            dialog.set_filename("untitled.rvms");

            dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
            dialog.add_button("_Open", Gtk::RESPONSE_OK);

            int result = Dialogs::run_dialog(&dialog);

            if (result == Gtk::RESPONSE_OK) {
                std::ifstream ifs{dialog.get_filename()};
                if (ifs) {
                    _rental_site = Rental_site{ifs};
                    _filename = dialog.get_filename();
                } else {
                    Dialogs::message("####Unable to load " + dialog.get_filename(), "ERROR");
                }
            }
            break;
        }
        case 9: { // Help
            Dialogs::message(_view.help(), "Help");
            break;
        }
        case 42: { // Easter egg
            _rental_site.add_vehicle(Vehicle{2002, "Ford", "Mustang", Body_style::SEDAN});
            _rental_site.add_vehicle(Vehicle{1918, "Chevy", "Four-Ninty", Body_style::TRUCK});
            _rental_site.add_vehicle(Vehicle{2014, "Hennessey", "Venom F5", Body_style::SEDAN});
            _rental_site.add_vehicle(Vehicle{2018, "Chrysler", "Pacifica", Body_style::MINIVAN});
            _rental_site.add_renter(Renter{"Larry", "31415927", "817-555-1212"});
            _rental_site.add_renter(Renter{"Curly", "27182818", "214-555-1212"});
            _rental_site.add_renter(Renter{"Mo", "14142135", "817-555-1212"});
            Dialogs::message("Added 4 vehicles and 3 stooges");
            break;
        }
        default: // Error
            Dialogs::message("### INVALID OPTION ###", "ERROR");
    }
}
