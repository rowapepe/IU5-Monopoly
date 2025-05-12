#pragma once
#include <iostream>
#include "../Board/Board.hpp"
#include "../Board/Cards.hpp"
#include "../Board/Cells.hpp"
#include <vector>
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
  void SetMoney(int m);
  int GetMoney();
  void PayTax();
  void BuyStreet( std::vector<Streets::Streets>& board,int index);
  void SellStreet( std::vector<Streets::Streets>& board,int index);
  void UpgradeStreet(std::vector<Streets::Streets>& board,int index);
  void DegradeStreet(std::vector<Streets::Streets>& board,int index);
  void PayRent(std::vector<Streets::Streets>& board,std::vector<Players> players,int index);
  static bool Bankrupt(std::vector<Players> players);

};
} // namespace Players
