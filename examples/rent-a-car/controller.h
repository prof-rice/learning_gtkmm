#ifndef __CONTROLLER_H
#define __CONTROLLER_H
#include "view.h"
#include "rental_site.h"

class Controller {
  public:
    Controller();
    Controller(Rental_site rental_site);
    void cli();
    void execute_cmd(int cmd);
    std::vector<std::vector<std::string>> vehicles();
  private:
    int get_int(std::string prompt, std::string title = "Integer Input");
    std::string vehicle_menu(bool rented=true, bool unrented=true);
    std::string renter_menu();
    Rental_site _rental_site;
    View _view;
    std::string _filename;
    std::string CANCEL_X = "Exit"; // Exception message indicating CANCEL was clicked
};
#endif
