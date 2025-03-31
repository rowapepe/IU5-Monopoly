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

  const std::vector<Streets::Streets> &getBoard() const;
};
} // namespace Board
