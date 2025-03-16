#pragma once
#include <iostream>
namespace{
const int maxPoint=25;
}
namespace Players {
class Players {
private:
  int index = 0;
  int money = 0;
  int position = 0;

public:
  Players();
  Players(int index, int money=15000, int position=0);
  void Move(int steps);
  void SetPos(int ind);
  void Print();
  void BuyStreet();
  void UpgradeStreet();
  void SellStreet();
  void PayRent();
  void Bankrupt();
  static void DeletePlayers(Players*& players);
};
} // namespace Players
