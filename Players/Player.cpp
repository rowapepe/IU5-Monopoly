#include "Player.hpp"

namespace Players {
Players::Players() : bankrupt(0), money(1500), position(0) {}
Players::Players(int bankrupt, int money, int position)
    : bankrupt(bankrupt), money(money), position(position) {}
void Players::Move(int steps, int boardSize) {
  position = (position + steps) % boardSize;
}

void Players::SetPosition(int newPosition) { this->position = newPosition; }

void Players::SellStreet(std::vector<Streets::Streets> &board, int index) {
  if (board[position].getType() != "улица") {
    std::cout << "Это не улица, нельзя купить";
    return;
  }

  if (board[position].getOwnerIndex() == -1) {
    std::cout << "Некуплена никем";
    return;
  }

  if (board[position].getOwnerIndex() == index) {
    board[position].setOwnerIndex(-1);
    money += board[position].getPrice() * 0.8;
    return;
  } else {
    std::cout << "Улица куплена не вами";
    return;
  }
}

void Players::BuyStreet(std::vector<Streets::Streets> &board, int index) {
  if (board[position].getType() != "улица" &&
      board[position].getType() != "имущество") {
    std::cout << "Это не улица или имущество, нельзя купить";
    return;
  }
  if (board[position].getOwnerIndex() == index) {
    std::cout << "Уже куплена вами";
    return;
  }
  if (board[position].getOwnerIndex() == -1) {
    if (board[position].getPrice() <= money) {
      board[position].setOwnerIndex(index);
      money -= board[position].getPrice();
      return;
    } else {
      std::cout << "Недостаточно денег";
      return;
    }
  } else {
    std::cout << "Улица куплена";
    return;
  }
}

void Players::Print() {
  std::cout << bankrupt << " " << money << " " << position << std::endl;
}

void Players::UpgradeStreet(std::vector<Streets::Streets> &board, int index) {
  if (board[position].getType() != "улица") {
    std::cout << "Это не улица, нельзя прокачать";
    return;
  }

  if (board[position].getLVL() == 4) {
    std::cout << "Максимальный уровень";
    return;
  }

  if (board[position].getOwnerIndex() == index) {
    if (board[position].getlvlcost() < money) {
      board[position].setLVL(board[position].getLVL() + 1);
      money -= board[position].getlvlcost();
      return;
    } else {
      std::cout << "Недостаточно денег";
      return;
    }
  } else {
    std::cout << "Не ваша улица";
    return;
  }
}

void Players::DegradeStreet(std::vector<Streets::Streets> &board, int index) {
  if (board[position].getType() != "улица") {
    std::cout << "Это не улица";
    return;
  }
  if (board[position].getLVL() == 0) {
    std::cout << "Минимальный уровень";
    return;
  }
  if (board[position].getOwnerIndex() == index) {

    board[position].setLVL(board[position].getLVL() - 1);
    money += board[position].getlvlcost() * 0.8;
    return;

  } else {
    std::cout << "Не ваша улица";
    return;
  }
}

void Players::SetMoney(int m) { money = m; }
int Players::GetMoney() const { return money; }
void Players::SetBankrupt(bool b) { bankrupt = b; }
bool Players::GetBankrupt() const { return bankrupt; }
int Players::GetPosition() const { return position; }

void Players::EarnMoney(int m) { this->money += m; }

void Players::PayRent(Streets::Streets &cell, std::vector<Players> &players) {
  if (cell.getOwnerIndex() == -1) {
    std::cout << "Улица никому не принадлежит, не надо ничего платить";
    return;
  }
  if (cell.getRent() < money) {
    players[cell.getOwnerIndex()].money += cell.getRent();
      money -= cell.getRent();
    return;
  } else {
    std::cout << "Недоcтаточно средств";
    return;
  }
}

void Players::PayTax(int taxAmount) {
  if (money < taxAmount) {
    std::cout << "Недостаточно денег";
    return;
  }
  money -= taxAmount;
}

bool Players::HasAllStreetsOfColor(const std::string &color,
                                   const std::vector<Streets::Streets> &board,
                                   const int &currentPlayerIndex) const {
  int totalStreetsInColor = 0;
  int ownedStreetsInColor = 0;

  for (const auto &street : board) {
    if (street.getColor() == color) {
      totalStreetsInColor++;
      if (street.getOwnerIndex() == (currentPlayerIndex + 1)) {
        ownedStreetsInColor++;
      }
    }
  }

  return ownedStreetsInColor == totalStreetsInColor;
}

bool Players::IsEnd(std::vector<Players> &players) {
  int k = 0;
  for (int i = 0; i < players.size(); ++i) {
    if (players[i].bankrupt == false) {
      k += 1;
    }
  }
  if (k == 1) {
    return true;
  }
  return false;
}

void Players::GoToJail() {
  isInJail = true;
  position = 10;
}

void Players::LeaveJail() { isInJail = false; }

bool Players::IsInJail() const { return isInJail; }
} // namespace Players
