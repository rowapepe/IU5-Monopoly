#pragma once
#include "Cells.hpp"
#include <vector>

namespace {}

namespace Board {
class Board {
  void initialize();

public:
  std::vector<Streets::Streets> board;
  Board();
};
} // namespace Board
