#include "Cells.hpp"

namespace {}

namespace Streets {
Streets::Streets(std::string type, std::string name, int price, int rent,
                 int ownerIndex, int posX, int posY, int streetlvl, int lvlcost,
                 std::string color)
    : type(type), name(name), price(price), rent(rent), ownerIndex(ownerIndex),
      posX(posX), posY(posY), streetlvl(streetlvl), lvlcost(lvlcost),
      color(color) {}

std::string Streets::getType() const { return type; }
std::string Streets::getName() const { return name; }
int Streets::getPrice() const { return price; }
int Streets::getRent() const {
  if (this->getLVL() > 0) {
    return rent * std::pow(2, getLVL());
  } else {
    return rent;
  }
}
int Streets::getOwnerIndex() const { return ownerIndex; }
int Streets::getPosX() const { return posX; }
int Streets::getPosY() const { return posY; }
int Streets::getLVL() const { return streetlvl; }
int Streets::getlvlcost() const { return lvlcost; }
std::string Streets::getColor() const { return color; }
int Streets::GetRentWithHouses(int houses) const {
  return rent * (1 + houses * 0.5);
}

void Streets::setType(const std::string &type) { this->type = type; }
void Streets::setName(const std::string &name) { this->name = name; }
void Streets::setPrice(int price) { this->price = price; }
void Streets::setRent(int rent) { this->rent = rent; }
void Streets::setOwnerIndex(int ownerIndex) { this->ownerIndex = ownerIndex; }
void Streets::setLVL(int lvl) { this->streetlvl = lvl; }
void Streets::setlvlcost(int cost) { this->lvlcost = cost; }
void Streets::setColor(std::string color) { this->color = color; };
} // namespace Streets
