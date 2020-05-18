#ifndef __RENTER_H
#define __RENTER_H
#include <string>
#include <ostream>
#include <istream>
#include <vector>

class Renter {
  public:
    Renter(std::string renter, std::string renter_dl, std::string renter_phone);
    Renter();
    Renter(std::istream& ist);
    void save(std::ostream& ost);
    std::string to_string() const;
    std::vector<std::string> to_strings();
    friend std::ostream& operator<<(std::ostream& ost, const Renter& renter);
  private:
    std::string _renter;
    std::string _renter_dl; // driver's license
    std::string _renter_phone;  
};
#endif
