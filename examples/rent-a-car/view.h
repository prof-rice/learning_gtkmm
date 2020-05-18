#ifndef __VIEW_H
#define __VIEW_H
#include "rental_site.h"
#include <string>
#include <vector>

class View {
  public:
    View(Rental_site& rental_site);
    std::string main_menu();
    std::vector<std::string> list_of_vehicles(bool rented=true, bool unrented=true);
    std::vector<std::string> list_of_renters();
    std::string help();
  private:
    Rental_site& _rental_site;
};
#endif
