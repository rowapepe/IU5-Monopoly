#include "Cells.hpp"

namespace {}

namespace Streets {
Streets::Streets(std::string type, std::string name, int price, int rent,
                 int ownerIndex,int streetlvl,int lvlcost)
    : type(type), name(name), price(price), rent(rent), ownerIndex(ownerIndex),streetlvl(streetlvl),lvlcost(lvlcost){
}

std::string Streets::getType() const { return type; }
std::string Streets::getName() const { return name; }
int Streets::getPrice() const { return price; }
int Streets::getRent() const { return rent; }
int Streets::getOwnerIndex() const { return ownerIndex; }
int Streets::getLVL() const { return streetlvl; }
int Streets::getlvlcost() const { return lvlcost; }

void Streets::setType(const std::string &type) { this->type = type; }
void Streets::setName(const std::string &name) { this->name = name; }
void Streets::setPrice(int price) { this->price = price; }
void Streets::setRent(int rent) { this->rent = rent; }
void Streets::setOwnerIndex(int ownerIndex) { this->ownerIndex = ownerIndex; }
void Streets::setLVL(int lvl) { this->streetlvl = lvl; }
void Streets::setlvlcost(int cost) { this->lvlcost = cost; }
} // namespace Streets
