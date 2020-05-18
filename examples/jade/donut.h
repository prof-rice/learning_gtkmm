#pragma once
#include "product.h"
#include <vector>
#include <ostream>
#include <istream>

enum Frosting {Unfrosted, Chocolate_top, Vanilla_top, Pink_top};
const std::vector<std::string> frosting_to_string =
    {"unfrosted", "chocolate", "vanilla", "pink"};

enum Filling {Unfilled, Creme, Bavarian, Strawberry};
const std::vector<std::string> filling_to_string =
    {"unfilled", "creme", "Bavarian", "strawberry"};

class Donut : public Product {
  public:
    Donut(std::string name, double price, double cost, Frosting frosting, bool sprinkles, Filling filling);
    virtual std::string type() override;
    std::string to_string() override;
    Donut(std::istream& ist);
    void save(std::ostream& ost) override;
  protected:
    Frosting _frosting;
    bool _sprinkles;
    Filling _filling;
};
