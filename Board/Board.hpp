#pragma once
#include "Cells.hpp"
#include <iostream>
#include <vector>

namespace {}

namespace Board {
class Board {
  void initialize();

public:
  std::vector<Streets::Streets> board;
  void printBoard();
  Board();
};
} // namespace Board
