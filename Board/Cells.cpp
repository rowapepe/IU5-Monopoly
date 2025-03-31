#include "Cells.hpp"

namespace {}

namespace Streets {
Streets::Streets(std::string type, std::string name, int price, int rent, int ownerIndex)
    : type(type), name(name), price(price), rent(rent), ownerIndex(ownerIndex) {}

std::string Streets::getType() const { return type; }
std::string Streets::getName() const { return name; }
int Streets::getPrice() const { return price; }
int Streets::getRent() const { return rent; }
int Streets::getOwnerIndex() const { return ownerIndex; }
} // namespace Streets
