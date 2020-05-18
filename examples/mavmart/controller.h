#ifndef __CONTROLLER_H
#define __CONTROLLER_H
#include "view.h"
#include "store.h"
#include <gtkmm.h>

class Controller {
  public:
    Controller(Gtk::Window* window, Store store);
    Controller(Gtk::Window* window);
    Controller();
    void gui();
    void cli();
    void execute_cmd(int cmd);
    std::string filename();
    int num_products();
    int num_orders();

    // GUI-specific data formats
    std::string all_products();

    // Commands (behaviors)
    void add_product();
    void list_all_products();
    void add_order();
    void list_all_orders();
    void load();
    void save(bool as = true);
    void easter_egg();
    void help();
  private:
    double get_double(std::string prompt, std::string title = "Enter Number");
    int get_int(std::string prompt, std::string title = "Enter Integer");
    std::string get_string(std::string prompt, std::string title = "Enter Text");
    Store _store;
    View _view;
    std::string _filename;
    Gtk::Window* _window;
    bool _gui;
};
#endif
