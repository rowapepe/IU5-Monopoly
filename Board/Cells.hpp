#pragma once
#include <string>

namespace {}

namespace Streets {
class Streets {
  std::string type;
  std::string name;
  int price;
  int rent;
  int ownerIndex;

public:
  Streets(std::string type, std::string name, int price, int rent, int ownerIndex);

  std::string getType() const;
  std::string getName() const;
  int getPrice() const;
  int getRent() const;
  int getOwnerIndex() const;
};
} // namespace Streets
