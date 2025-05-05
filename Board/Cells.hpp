#pragma once

#include <string>

namespace Streets {
class Streets {
  std::string type;
  std::string name;
  int price;
  int rent;
  int ownerIndex;
  int streetlvl;
  int lvlcost;

public:
  Streets(std::string type, std::string name, int price, int rent,
          int ownerIndex,int streetlvl=1,int lvlcost=1500);
  std::string getType() const;
  std::string getName() const;
  int getPrice() const;
  int getRent() const;
  int getOwnerIndex() const;
  int getLVL() const;
  int getlvlcost() const;

  void setType(const std::string &type);
  void setName(const std::string &name);
  void setPrice(int price);
  void setRent(int rent);
  void setOwnerIndex(int ownerIndex);
  void setLVL(int lvl);
  void setlvlcost(int cost);
};
} // namespace Streets
