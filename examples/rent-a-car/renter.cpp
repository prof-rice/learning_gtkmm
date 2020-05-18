#include "renter.h"

Renter::Renter(std::string renter, std::string renter_dl, std::string renter_phone)
    : _renter{renter}, _renter_dl{renter_dl}, _renter_phone{renter_phone} { }
Renter::Renter() : Renter("", "", "") { }

Renter::Renter(std::istream& ist) {
    std::getline(ist, _renter);
    std::getline(ist, _renter_dl);
    std::getline(ist, _renter_phone);
}
void Renter::save(std::ostream& ost) {
    ost << _renter << std::endl;
    ost << _renter_dl << std::endl;
    ost << _renter_phone << std::endl;
}

std::vector<std::string> Renter::to_strings() {
    std::vector<std::string> result;
    result.push_back(_renter);
    result.push_back(_renter_dl);
    result.push_back(_renter_phone);
    return result;
}

std::string Renter::to_string() const {
    return _renter + ", " + _renter_dl + ", " + _renter_phone;
}

std::ostream& operator<<(std::ostream& ost, const Renter& renter) {
    ost << renter.to_string();
    return ost;
}

 
