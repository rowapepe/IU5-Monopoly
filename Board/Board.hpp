#pragma once
#include "Cells.hpp"
#include <vector>

namespace {}

namespace Board {
class Board {
  std::vector<Streets::Streets> board;
  void initialize();

public:
  Board();
};
} // namespace Board
