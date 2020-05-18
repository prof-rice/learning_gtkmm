#include "controller.h"
#include <dirent.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <experimental/filesystem>
#include "dialogs.h"

Controller::Controller() : Controller(nullptr) { }
Controller::Controller(Gtk::Window* window) : Controller(window, Store{"Mavmart"}) { }
Controller::Controller(Gtk::Window* window, Store store) 
    : _window{window}, _store{store}, _view{View{_store}}, _filename{"untitled.dat"}, _gui{true} { }

std::string Controller::filename() {return _filename;}
int Controller::num_products() {return _store.num_products();}
int Controller::num_orders() {return _store.num_orders();}

double Controller::get_double(std::string prompt, std::string title) {
    while(true) {
        try {
            std::string s;
            if (_gui) {
                s = Dialogs::input(prompt, title);
                if (s == "" || s == "CANCEL") break;
            } else {
                std::cout << prompt << "? ";
                std::getline(std::cin, s);
                if (s == "") break;
            }
            std::istringstream iss{s};
            double d;
            iss >> d;
            return d;
        } catch(std::runtime_error e) {
            if (_gui) Dialogs::message("#### Error: Invalid input: " + std::string{e.what()});
            else std::cerr << "#### Error: Invalid input: " << e.what() << std::endl;
        }
    }
    throw std::runtime_error{prompt + " was not entered"};
}
int Controller::get_int(std::string prompt, std::string title) {
    while(true) {
        try {
            std::string s;
            if (_gui) {
                s = Dialogs::input(prompt, title);
                if (s == "" || s == "CANCEL") break;
            } else {
                std::cout << prompt << "? ";
                std::getline(std::cin, s);
                if (s == "") break;
            }
            std::istringstream iss{s};
            int d;
            iss >> d;
            return d;
        } catch(std::runtime_error e) {
            if (_gui) Dialogs::message("#### Error: Invalid input: " + std::string{e.what()});
            else std::cerr << "#### Error: Invalid input: " << e.what() << std::endl;
        }
    }
    throw std::runtime_error{prompt + " was not entered"};
}
std::string Controller::get_string(std::string prompt, std::string title) {
    while(true) {
        try {
            std::string s;
            if (_gui) {
                s = Dialogs::input(prompt, title);
                if(s == "CANCEL") break;
            } else {
                std::cout << prompt << "? ";
                std::getline(std::cin, s);
            }
            return s;
        } catch(std::runtime_error e) {
            if (_gui) Dialogs::message("#### Error: Invalid input: " + std::string{e.what()});
            else std::cerr << "#### Error: Invalid input: " << e.what() << std::endl;
        }
    }
    throw std::runtime_error{prompt + " was not entered"};
}
void Controller::cli() {
    _gui = false;
    while(true) {
        try {
            std::cout << _view.main_menu(_gui);
            int cmd = get_int("Command");
            if (cmd == 0) break;
            execute_cmd(cmd);
        } catch (std::runtime_error e) {
            std::cerr << "#### Error: Invalid input" << std::endl;
        }
    }
}
void Controller::gui() {
    _gui = true;  // Signal for GUI dialogs instead of CLI
    while(true) {
        try {
            int cmd = get_int(_view.main_menu(_gui), "Main Menu");
            if (cmd == 0) break;
            execute_cmd(cmd);
        } catch (std::runtime_error e) {
            break;
        }
    }
}

void Controller::execute_cmd(int cmd) {
    switch(cmd) {
        case 1: add_product(); break;
        case 2: list_all_products(); break;
        case 4: add_order(); break;
        case 5: list_all_orders(); break;
        case 7: load(); break;
        case 8: save(); break;
        case 9: help(); break;
        case 42: easter_egg(); break;
        default: if (_gui) Dialogs::message("#### Invalid command");
                 else std::cerr << "#### Invalid command" << std::endl;
    }
}

void Controller::add_product() {
    try {
      if (_gui) {
        std::string name;
        double price;

        // Create a new dialog
        Gtk::Dialog *dialog = new Gtk::Dialog("Add Product", *_window);

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

        // Show dialog
        dialog->add_button("Cancel", 0);
        dialog->add_button("OK", 1);
        dialog->show_all();
        int result = dialog->run();

        dialog->close();
        while (Gtk::Main::events_pending())  Gtk::Main::iteration();

        if (result == 1) {
            name = e_name.get_text();
            price = std::stod(e_price.get_text());
            _store.add_product(Product{name, price});
        }

        delete dialog;
      } else {
        // std::string name;
        // std::cout << "Product name? ";
        // std::getline(std::cin, name);
        std::string name = get_string("Product name? ", "New Product");

        if (name.empty()) throw std::runtime_error{"Empty product name"};
        double price = get_double("Price");
        _store.add_product(Product{name, price});
      }
    } catch(std::runtime_error e) {
        if (_gui) Dialogs::message("#### Error: Invalid input: " + std::string{e.what()});
        else std::cerr << "#### Add Product aborted: " << e.what() << std::endl;
    }
}

std::string Controller::all_products() {
    std::ostringstream oss;
    oss << "Item Description             Price\n";
    for(int i=0; i<_store.num_products(); ++i)
        oss << std::setw(4)  << std::right << i << " " 
            << std::setw(20) << std::left  << _store.product(i).name() << " "
            << std::setw(8)  << std::right << std::fixed << std::setprecision(2) << _store.product(i).price() 
            << std::endl;
    return oss.str();
}


void Controller::list_all_products() {
    if (_gui) {
        std::ostringstream oss;
        for(int i=0; i<_store.num_products(); ++i)
            oss << i << ") " << _store.product(i) << std::endl;
        Dialogs::message(oss.str(), "Available Products");
    } else {
        std::cout << "\nAvailable Products\n==================\n";
        for(int i=0; i<_store.num_products(); ++i)
            std::cout << i << ") " << _store.product(i) << std::endl;
    }
}

void Controller::add_order() {
    try {
        // std::string email;
        // std::cout << "Customer email address? ";
        // std::getline(std::cin, email);
        std::string email = get_string("Email address? ", "Place Order");

        if (email.empty()) throw std::runtime_error{"Empty email address"};
        int order_num = _store.create_order(email);

        while(true) {
            // list_all_products();
            std::ostringstream oss;
            for(int i=0; i<_store.num_products(); ++i)
                oss << i << ") " << _store.product(i) << std::endl;
            oss << "\nProduct number to add (-1 when done) ";

            int product_num = get_int(oss.str(), "Place Order");
            if (0 <= product_num && product_num < _store.num_products()) {
                int product_quantity = get_int("Quantity", "Place Order");
                if (0 <= product_quantity)
                    _store.add_to_order(order_num, Product_order{_store.product(product_num), product_quantity});
                else
                    if (_gui) Dialogs::message("#### Invalid quantity: " + std::to_string(product_quantity));
                    else std::cerr << "#### Invalid quantity: " << product_quantity << std::endl;
            } else if (product_num == -1) {
                break;
            } else {
                if(_gui) Dialogs::message("#### No such product number: " + std::to_string(product_num));
                else std::cerr << "#### No such product number: " << product_num << std::endl;
            }
            if (_gui) {
                std::ostringstream oss;
                oss << _store.order(order_num);
                Dialogs::message(oss.str(), "Current Order #" + std::to_string(order_num));
            } else {
                std::cout << "\n\nCurrent Products in Order " << order_num << "\n=============================\n" 
                          << _store.order(order_num) << std::endl << std::endl;
            }
        }
        if (_gui) {
            std::ostringstream oss;
            oss <<  _store.order(order_num)
                << "Thank you for shopping at Mavmart!" << std::endl;
            Dialogs::message(oss.str(), "Order #" + std::to_string(order_num));
        } else {
            std::cout << "\n\nOrder #" << order_num << "\n" << _store.order(order_num)
                      << "Thank you for shopping at Mavmart!" << std::endl;
        }
    } catch (std::runtime_error e) {
        if (_gui) Dialogs::message("#### Place Order aborted: " + std::string{e.what()});
        else std::cerr << "#### Place Order aborted: " << e.what() << std::endl;
    }
}
void Controller::list_all_orders() {
    if (_gui) {
        std::ostringstream oss;
        for(int i=0; i<_store.num_orders(); ++i)
            oss << i << ") " << _store.order(i) << std::endl;
        Dialogs::message(oss.str(), "Available Orders");
    } else {
        for(int i=0; i<_store.num_orders(); ++i)
            std::cout << "Order #" << i << "\n" << _store.order(i) << std::endl;
    }
}
void Controller::load() {
/*  // The C way to list all files in a directory
    DIR *dpdf;
    struct dirent *epdf;
    dpdf = opendir(".");
    if (dpdf != NULL) while (epdf = readdir(dpdf)) std::cout << epdf->d_name << std::endl;
*/
    // The NEW C++ way to list all files ending in .dat in a directory (experimental until C++ 8)
    //   ===>> You do NOT need to know this for any exam - just "for advanced students" :-)
    //   And, you need a special linker flag -lstdc++fs at the END of the linker line
    //   See the Makefile for an example
    // Add "namespace fs = std::experimental::filesystem;" after the #include lines and this becomes simply
    //   for(auto& p: fs::directory_iterator(".")) {

    try {
        if (_gui) {
            Gtk::FileChooserDialog dialog(*_window, "Please choose a file",
                Gtk::FileChooserAction::FILE_CHOOSER_ACTION_OPEN);

            auto filter_dat = Gtk::FileFilter::create();
            filter_dat->set_name("DAT files");
            filter_dat->add_pattern("*.dat");
            dialog.add_filter(filter_dat);
 
            auto filter_text = Gtk::FileFilter::create();
            filter_text->set_name("Text files");
            filter_text->add_mime_type("text/plain");
            dialog.add_filter(filter_text);

            auto filter_any = Gtk::FileFilter::create();
            filter_any->set_name("Any files");
            filter_any->add_pattern("*");
            dialog.add_filter(filter_any);

            dialog.set_filename("untitled.dat");

            dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
            dialog.add_button("_Open", Gtk::RESPONSE_OK);

            int result = dialog.run();

            if (result != Gtk::RESPONSE_OK) return;
            _filename = dialog.get_filename();
        } else {
            std::ostringstream file_list;
            for(auto& p: std::experimental::filesystem::directory_iterator(".")) {
                if(p.path().extension() == ".dat") file_list << p << '\n';
            }
            file_list << "\nFilename to load?";
            _filename = get_string(file_list.str(), "Load Store");
            if (_filename == "CANCEL") return;
        }
        std::ifstream ifs{_filename};
        if (ifs) _store = Store{ifs};
        else if (_gui) Dialogs::message("Unable to open for load: " + _filename, "ERROR");
        else std::cerr << "Unable to open for load: " << _filename << std::endl;
    } catch(std::exception e) {
        if(_gui) Dialogs::message("Load aborted", "Load Store");
        else std::cerr << "Load aborted" << std::endl;
    }
}
void Controller::save(bool as) {
    try {
        if (_gui && as) {
            Gtk::FileChooserDialog dialog(*_window, "Please choose a file",
                  Gtk::FileChooserAction::FILE_CHOOSER_ACTION_SAVE);
            auto filter_dat = Gtk::FileFilter::create();
            filter_dat->set_name("DAT files");
            filter_dat->add_pattern("*.dat");
            dialog.add_filter(filter_dat);
 
            auto filter_any = Gtk::FileFilter::create();
            filter_any->set_name("Any files");
            filter_any->add_pattern("*");
            dialog.add_filter(filter_any);

            dialog.set_filename("untitled.dat");

            dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
            dialog.add_button("_Save", Gtk::RESPONSE_OK);

            int result = dialog.run();

            if (result != Gtk::RESPONSE_OK) return;
            _filename = dialog.get_filename();
        } else if (!_gui) {
            _filename = get_string("Filename to save? ", "Save Store");
            if (_filename == "CANCEL") return;
        }
        std::ofstream ofs{_filename};
        if (ofs) _store.save(ofs);
        else if (_gui) Dialogs::message("Unable to open for save: " + _filename, "ERROR");
        else std::cerr << "Unable to open for save: " << _filename << std::endl;
    } catch (std::exception e) {
        if(_gui) Dialogs::message("Save aborted", "Save Store");
        else std::cerr << "Save aborted" << std::endl;
    }
}
void Controller::easter_egg() {
        _store.add_product(Product {"Hamburger", 4.00});
        _store.add_product(Product {"Hot Dog", 2.00});
        _store.add_product(Product {"Sandwich", 3.50});
        _store.add_product(Product {"Fries", 0.75});
        _store.add_product(Product {"Chips", 1.50});
        _store.add_product(Product {"Pickle", 0.25});
        _store.add_product(Product {"Coke", 1.25});
        _store.add_product(Product {"Diet Coke", 1.25});
        _store.add_product(Product {"Dr Pepper", 1.25});
}
void Controller::help() {
    if (_gui) Dialogs::message(_view.help(_gui), "Help");
    else std::cout << _view.help() << std::endl;
}

