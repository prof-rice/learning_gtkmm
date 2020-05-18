#include "mainwin.h"

void Mainwin::on_easteregg_click() {
        _emp->add_container(
            Mice::Container{"Cone", "Crispy airy delight", 0.25, 0.50, 2});
        _emp->add_container(
            Mice::Container{"Waffle Cone", "Crunchy wrapped waffle cake", 0.35, 0.75, 3});
        _emp->add_scoop(
            Mice::Scoop{"Chocolate", "Rich smooth chocolate ice cream", 0.20, 0.50});
        _emp->add_scoop(
            Mice::Scoop{"Vanilla", "Real vanilla bean ice cream", 0.20, 0.50});
        _emp->add_scoop(
            Mice::Scoop{"Strawberry", "Chunks of strawberry wrapped in vanilla ice cream", 0.20, 0.50});
        _emp->add_topping(
            Mice::Topping{"Cherry", "Classic marichino cherry", 0.1, 0.2, 0});
        _emp->add_topping(
            Mice::Topping{"Chocolate Sauce", "Rich thick chocolate", 0.1, 0.25, 0});
        _emp->add_topping(
            Mice::Topping{"Whipped Cream", "Real sweet cream whipped to perfection", 0.1, 0.2, 0});
        _emp->add_server(
            Mice::Server{"Penny", "BBT", "817-555-1212", 10.25}); 
        _emp->add_server(
            Mice::Server{"Rachel Green", "Friends", "817-555-1213", 8.75}); 
        _emp->add_server(
            Mice::Server{"Henry Jackson", "BWidowers", "817-555-1214", 15.00}); 
        _emp->add_customer(
            Mice::Customer{"Columbo", "LAPD", "817-555-1312"});
        _emp->add_customer(
            Mice::Customer{"Elton John", "Glitter", "817-555-1313"});

        // Display acknowledgement
        Gtk::MessageDialog dialog{*this, "Added 2 containers, 3 scoops, 3 toppings,\n3 servers, 2 customers"};
        dialog.run();
        dialog.close();
 } 

