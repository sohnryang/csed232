#pragma once

#include "artist.hpp"

#include <vector>

class sobelx : public artist {
private:
  std::vector<std::vector<int>> diff_x;

public:
  sobelx(int, int, const std::vector<int> &);
  char mapper(int, int);
};
