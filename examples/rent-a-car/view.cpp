#include "view.h"
#include <sstream>

View::View(Rental_site& rental_site) : _rental_site{rental_site} { }

std::string View::main_menu() { 
    return R"(
<span font='18' weight='bold'>C1325 Rental Vehicle Management System<sup><small>™</small></sup></span>

<span weight='bold' underline='double'>Vehicle</span>                    <span weight='bold' underline='double'>Renter</span>
(1) Add vehicle         (5) Add renter
(2) List all vehicles   (6) List all renters
(3) Rent vehicle
(4) Return vehicle

<span weight='bold' underline='double'>File</span>                      <span weight='bold' underline='double'>Utility</span>
(7) Save                (9) <span color='#007f00'><b>Help</b></span>
(8) Load                (0) Exit
)";
}

std::vector<std::string> View::list_of_vehicles(bool rented, bool unrented) {
    std::vector<std::string> result;
    int vehicle_num = 0;
    for (std::string s : _rental_site.vehicles(rented, unrented)) {
        if (s.size() > 0) {
            std::ostringstream ost;
            ost << vehicle_num << ") " << s;
            result.push_back(ost.str());
        }
        ++vehicle_num;
    }
    return result;
}

std::vector<std::string> View::list_of_renters() {
    std::vector<std::string> result;
    int renter_num = 0;
    for (std::string r : _rental_site.renters()) {
        std::ostringstream ost;
        ost << renter_num++ << ") " << r;
        result.push_back(ost.str());
    }
    return result;
}

std::string View::help() {
    return R"(
<span font='18' weight='bold'>C1325 Rental Vehicle Management System<sup><small>™</small></sup></span>
by Professor George F. Rice
<span font='7'>Copyright 2018. Licensed under the Gnu General Public License 3.0
https://www.gnu.org/licenses/gpl-3.0.en.html</span>

This program manages a fleet of rental vehicles.

<b>Adding a vehicle</b> (option 1) requires a year, make, model, and body style.
The year may be any integer; the make and model are arbitrary strings.
The body style is selected from a list. Adding a body style requires
a program change.

<b>Listing all vehicles</b> (option 2) displays all information known about
the vehicles, including the identity of their respective renters.

<b>Renting a vehicle</b> (option 3) requires a renter's name, driver's license
number, and phone number. All 3 are arbitrary strings.

<b>Returning a vehicle</b> (option 4) requires no additional information.

<b>Adding a renter</b> (option 5) requires a name, driver's license number, 
and phone number. All three are arbitrary, unvalidated strings.

<b>Listing all renters</b> (option 6) displays all information known about renters.

<b>Save Data</b> (option 7) writes all data to file "untitled.txt" in the current folder.

<b>Load Data</b> (option 8) replaces any existing data <span color='red'>without warning</span>
from file "untitled.txt" in the current folder.

<i>Undocumented option 42 adds test data.</i>
)";
}
