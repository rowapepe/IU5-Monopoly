#pragma once

#include <string>
#include <cmath>

namespace Streets {
class Streets {
  std::string type;
  std::string name;
  int price;
  int rent;
  int ownerIndex;
  int posX;
  int posY;
  int streetlvl;
  int lvlcost;
  std::string color;

public:
  Streets(std::string type, std::string name, int price, int rent,
          int ownerIndex, int posX, int posY, int streetlvl, int lvlcost,
          std::string color);
  std::string getType() const;
  std::string getName() const;
  int getPrice() const;
  int getRent() const;
  int getOwnerIndex() const;
  int getPosX() const;
  int getPosY() const;
  int getLVL() const;
  int getlvlcost() const;
  std::string getColor() const;
  int GetRentWithHouses(int houses) const;

  void setType(const std::string &type);
  void setName(const std::string &name);
  void setPrice(int price);
  void setRent(int rent);
  void setOwnerIndex(int ownerIndex);
  void setLVL(int lvl);
  void setlvlcost(int cost);
  void setColor(std::string color);
};
} // namespace Streets
