#ifndef __VEHICLE_H
#define __VEHICLE_H
#include "renter.h"
#include <string>
#include <ostream>
#include <istream>


enum Body_style{SEDAN, HATCHBACK, MINIVAN, TRUCK, CROSSOVER, SUV};
const int NUM_BODY_STYLES = 6;

class Vehicle {
  public:
    Vehicle(int year, std::string make, std::string model, Body_style body_style);
    Vehicle(std::istream& ist);
    void save(std::ostream& ost);

    void rent_vehicle(Renter renter);
    void return_vehicle();
    std::vector<std::string> to_strings();
    std::string make() const;
    std::string model() const;
    int year() const;
    Body_style body_style() const;
    bool is_rented();
    friend std::ostream& operator<<(std::ostream& ost, const Vehicle& vehicle);
  private:
    std::string body_style_to_string() const;
    std::string to_string() const;
    int _year;
    std::string _make;
    std::string _model;
    Body_style _body_style;
    bool _is_rented;
    Renter _renter;
};
#endif
