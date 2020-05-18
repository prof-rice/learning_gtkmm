#ifndef __VIEW_H
#define __VIEW_H
#include "store.h"
#include <string>
#include <vector>

class View {
  public:
    View(Store& store);
    std::string main_menu(bool _gui = false);
    //std::vector<std::string> list_of_vehicles();
    std::string help(bool _gui = false);
  private:
    Store& _store;
};
#endif
