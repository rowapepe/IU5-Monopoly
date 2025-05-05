#include "Board.hpp"

namespace {}

namespace Board {
Board::Board() { initialize(); }
void Board::initialize() {
  board.emplace_back("старт", "Старт", 0, 0, -1,5);
  board.emplace_back("улица", "Житная ул.", 60, 2, -1);
  board.emplace_back("казна", "Общественная казна", 0, 0, -1);
  board.emplace_back("улица", "ул. Нагатинская", 60, 4, -1);
  board.emplace_back("налог", "Подоходный налог", 0, 200, -1);
  board.emplace_back("имущество", "Рижская ж/д", 200, 25, -1);
  board.emplace_back("улица", "Варшавское шоссе", 100, 6, -1);
  board.emplace_back("шанс", "Шанс", 0, 0, -1);
  board.emplace_back("улица", "ул. Огарева", 100, 6, -1);
  board.emplace_back("улица", "ул. Первая Парковая", 120, 8, -1);
  board.emplace_back("тюрьма", "Тюрьма", 0, 0, -1);
  board.emplace_back("улица", "ул. Полянка", 140, 10, -1);
  board.emplace_back("имущество", "Электростанция", 150, 18, -1);
  board.emplace_back("улица", "ул. Сретенка", 140, 12, -1);
  board.emplace_back("улица", "Ростовская наб.", 160, 12, -1);
  board.emplace_back("имущество", "Курская ж/д", 200, 25, -1);
  board.emplace_back("улица", "Рязанский проспект", 180, 14, -1);
  board.emplace_back("казна", "Общественная казна", 0, 0, -1);
  board.emplace_back("улица", "ул. Вавилова", 180, 14, -1);
  board.emplace_back("улица", "Рублевское шоссе", 200, 16, -1);
  board.emplace_back("стоянка", "Бесплатная стоянка", 0, 0, -1);
  board.emplace_back("улица", "ул. Тверская", 220, 18, -1);
  board.emplace_back("шанс", "Шанс", 0, 0, -1);
  board.emplace_back("улица", "Пушкинская ул.", 220, 18, -1);
  board.emplace_back("улица", "Площадь Маяковского", 240, 20, -1);
  board.emplace_back("имущество", "Казанская ж/д", 200, 25, -1);
  board.emplace_back("улица", "ул. Грузинский вал", 260, 22, -1);
  board.emplace_back("улица", "Новинский бульвар", 260, 24, -1);
  board.emplace_back("имущество", "Водоканал", 150, 18, -1);
  board.emplace_back("улица", "Смоленская площадь", 280, 26, -1);
  board.emplace_back("тюрьма", "Отправляйся в тюрьму", 0, 0, -1);
  board.emplace_back("улица", "ул. Щусева", 300, 28, -1);
  board.emplace_back("улица", "Гоголевский бульвар", 300, 28, -1);
  board.emplace_back("казна", "Общественная казна", 0, 0, -1);
  board.emplace_back("улица", "Кутузовский проспект", 320, 30, -1);
  board.emplace_back("имущество", "Ленинградская ж/д", 200, 25, -1);
  board.emplace_back("шанс", "Шанс", 0, 0, -1);
  board.emplace_back("улица", "ул. Малая Бронная", 350, 32, -1);
  board.emplace_back("налог", "Сверхналог", 0, 100, -1);
  board.emplace_back("улица", "ул. Арбат", 400, 34, -1);
}
void Board::printBoard(){
  for(int i = 0;i<board.size();++i){
    std::cout<<board[i].getName()<<' '<<board[i].getOwnerIndex()<<' '<<i<<' '<<board[i].getLVL()<<std::endl;
  }
}
} // namespace Board
