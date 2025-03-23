#pragma once
#include <string>

namespace {}

namespace Streets {
class Streets {
  std::string type;
  std::string name;
  int price;
  int rent;

public:
  Streets(std::string type, std::string name, int price, int rent);

  std::string getType() const;
  std::string getName() const;
  int getPrice() const;
  int getRent() const;
};
} // namespace Streets
