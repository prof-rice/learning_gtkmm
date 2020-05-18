#include "mainwin.h"
#include <exception>
#include <stdexcept>

void Mainwin::on_fill_order_click() {
    int order = select_order(Mice::Order_state::Unfilled);
    if (order < 0) return;
    int server = select_server();
    if (server < 0) return;

    try {
        _emp->order(order).fill(_emp->server(server));
    } catch(std::runtime_error e) {
        Gtk::MessageDialog dialog{*this, e.what()};
        dialog.run();
        dialog.close();
        return;
    }
}

