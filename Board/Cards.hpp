#pragma once
#include <string>
#include <vector>

namespace Cards {
enum class EffectType { Move, Money };

struct Card {
  std::wstring description;
  EffectType effect;
  int value;
};

class Deck {
private:
  std::vector<Card> cards;
  size_t currentIndex = 0;

public:
  Deck(std::string type = "шанс");
  void shuffle();
  Card drawCard();
};
} // namespace Cards
