#pragma once
#include "../Board/Board.hpp"
#include "../Board/Cards.hpp"
#include "../Board/Cells.hpp"
#include <iostream>
#include <vector>
namespace {
const int maxPoint = 25;
}
namespace Players {
class Players {
private:
  bool bankrupt = 0;
  int money = 0;
  int position = 0;
  bool isInJail = false;

public:
  Players();
  Players(int bankrupt, int money = 1500, int position = 0);
  void Move(int steps, int boardSize);
  void Print();
  void SetMoney(int m);
  void SetBankrupt(bool b);
  bool GetBankrupt() const;

  int GetMoney() const;
  int GetPosition() const;
  void SetPosition(int newPosition);

  void BuyStreet(std::vector<Streets::Streets> &board, int index);
  void SellStreet(std::vector<Streets::Streets> &board, int index);
  void UpgradeStreet(std::vector<Streets::Streets> &board, int index);
  void DegradeStreet(std::vector<Streets::Streets> &board, int index);

  void PayRent(Streets::Streets &board,
               std::vector<Players> &players);
  void PayTax(int taxAmount);
  void EarnMoney(int m);

  void GoToJail();
  void LeaveJail();
  bool IsInJail() const;

  static bool IsEnd(std::vector<Players> &players);

};
} // namespace Players
