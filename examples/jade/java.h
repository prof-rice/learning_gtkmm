#pragma once
#include "product.h"
#include <vector>
#include <ostream>
#include <istream>

enum Darkness {Blonde, Light, Medium, Dark, Extra_dark};
const std::vector<std::string> darkness_to_string =
        {"Blonde", "Light", "Medium", "Dark", "Extra Dark"};

enum Shot {None, Chocolate, Vanilla, Peppermint, Hazelnut, Caramel};
const std::vector<std::string> shot_to_string =
    {"none", "chocolate", "vanilla", "peppermint", "hazelnut", "caramel"};

class Java : public Product {
  public:
    Java(std::string name, double price, double cost, Darkness darkness);
    void add_shot(Shot shot);
    virtual std::string type() override;
    std::string to_string() override;
    Java(std::istream& ist);
    void save(std::ostream& ost) override;
  protected:
    Darkness _darkness;
    std::vector<Shot> _shots;
};
    
