#ifndef __CONTROLLER_H
#define __CONTROLLER_H

#include <vector>
#include <iostream>
#include <climits> // INT_MIN, INT_MAX
#include <cfloat>  // DBL_MAX
#include "store.h"
#include "view.h"


class Controller {
  public:
    Controller(Store& store);
    Controller();

  // The command line interface
    int cli();

    // The commands
    void add_sweet();
    void list_sweets();
    void place_order();
    void list_order();
  protected:
    char get_char(std::string prompt, char min = ' ', char max = '~');
    int get_int(std::string prompt, int min = INT_MIN, int max = INT_MAX);
    double get_double(std::string prompt, double min = -DBL_MAX, double max = DBL_MAX);
  private:
    Store& _store;
    View _view;
};
#endif
