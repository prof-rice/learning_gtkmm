#include "mainwin.h"
#include <exception>
#include <stdexcept>

void Mainwin::on_pay_for_order_click() {
    int order = select_order(Mice::Order_state::Filled);
    if (order < 0) return;

    try {
        _emp->order(order).pay();
    } catch(std::runtime_error e) {
        Gtk::MessageDialog dialog{*this, e.what()};
        dialog.run();
        dialog.close();
        return;
    }
}

