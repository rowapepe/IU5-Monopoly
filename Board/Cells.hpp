#pragma once

#include <string>

namespace Streets {
class Streets {
  std::string type;
  std::string name;
  int price;
  int rent;
  int ownerIndex;

public:
  Streets(std::string type, std::string name, int price, int rent,
          int ownerIndex);
  std::string getType() const;
  std::string getName() const;
  int getPrice() const;
  int getRent() const;
  int getOwnerIndex() const;

  void setType(const std::string &type);
  void setName(const std::string &name);
  void setPrice(int price);
  void setRent(int rent);
  void setOwnerIndex(int ownerIndex);
};
} // namespace Streets
