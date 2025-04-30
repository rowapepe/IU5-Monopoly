#pragma once
#include <iostream>
#include "../Board/Board.hpp"
#include "../Board/Cards.hpp"
#include "../Board/Cells.hpp"
namespace{
const int maxPoint=25;
}
namespace Players {
class Players {
private:
  bool bankrupt=0;
  int money = 0;
  int position = 0;

public:
  Players();
  Players(int bankrupt, int money=15000, int position=0);
  void Move(int steps);
  void Print();
  void BuyStreet( std::vector<Streets::Streets>& board,int index);
  void UpgradeStreet();
  void SellStreet();
  void PayRent();
  void Bankrupt();
  static void DeletePlayers(Players*& players);
};
} // namespace Players
