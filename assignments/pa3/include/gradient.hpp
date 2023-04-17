#pragma once

#include "artist.hpp"

#include <vector>

class gradient : public artist {
private:
  std::vector<std::vector<int>> diff_x, diff_y;

public:
  gradient(int, int, const std::vector<int> &);
  char mapper(int, int);
};
