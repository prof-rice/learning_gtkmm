#ifndef __VIEW_H
#define __VIEW_H

#include "store.h"

class View {
  public:
    View(Store& store);
    void splash();
    void main_menu();
    void menu();
    void orders();
    void help();
  private:
    Store& _store;
};

#endif
