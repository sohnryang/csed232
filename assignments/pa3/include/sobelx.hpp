#pragma once

#include "artist.hpp"

#include <vector>

class sobelx : public artist {
public:
  sobelx(int, int, const std::vector<int> &);
  char mapper(int, int);
};
