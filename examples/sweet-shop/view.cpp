#include "view.h"
#include <iostream>

View::View(Store& store) : _store{store} { }
void View::splash() {
    std::string clear{"\033c"};
    std::cout << clear << R"(

            ============================
               Mav's Ultra Sweet Shop
            ============================

)";
}
void View::main_menu() {
    std::cout << R"(
        Show the (M)enu      Add a new (S)weet
        Place an (O)rder     (L)ist an order
        e(X)it

)";
}

void View::menu() {
    for(int i=0; i<_store.num_sweets(); ++i) 
        std::cout << "        " << i << ") " << _store.sweet(i) << std::endl;
}

void View::orders() {
     for(int i=0; i<_store.num_orders(); ++i) 
        std::cout << "        Order " << i << ":\n" << _store.order(i) << std::endl;
  
}
void View::help() { // You may select any license you please; this is just one example
    std::cout << R"(

    Mav's Ultra Sweet Shop (MUSS)
    =============================

    Manage a sweet shop filled with sweets.
    Copyright 2019 George F. Rice

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

)";

}

