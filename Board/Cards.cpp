#include "Cards.hpp"
#include <algorithm>
#include <random>

namespace Cards {
Deck::Deck(std::string type ) {
  if (type == "шанс") {
    cards = {{L"Пройдите на старт", EffectType::Move, 0},
             {L"Переместитесь на улицу Пушкина", EffectType::Move, 23},
             {L"Отправляйтесь на улицу Арбат", EffectType::Move, 39},
             {L"Отправляйтесь до Рижской ж/д", EffectType::Move, 5},
             {L"Идите до тюрьмы", EffectType::Move, 10},

             {L"Получите $100 за продажу акций", EffectType::Money, 100},
             {L"Штраф за парковку: $50", EffectType::Money, -50},
             {L"Выиграли в лотерею: $200", EffectType::Money, 200},
             {L"Штраф за превышение скорости: $15", EffectType::Money, -15},
             {L"Выиграли в конкурсе красоты: $15", EffectType::Money, 15}};
  } else if (type == "казна") {
    cards = {
        {L"Расходы на лечение у врача, заплатите: $50", EffectType::Money, -50},
        {L"Сбор на ремонт, заплатите: $40", EffectType::Money, -40},
        {L"Банковская ошибка в пользу вас, получите: $200", EffectType::Money,
         200},
        {L"Вы заняли второе место на конкурсе красоты получите: $10",
         EffectType::Money, 10}};
  }
  shuffle();
}

void Deck::shuffle() {
  static std::random_device rd;
  static std::mt19937 rng(rd());
  std::shuffle(cards.begin(), cards.end(), rng);
  currentIndex = 0;
}

Card Deck::drawCard() {
  if (currentIndex >= cards.size()) {
    shuffle();
  }
  return cards[currentIndex++];
}
} // namespace Cards
