#pragma once

#include <vector>

#include <artist.hpp>

class sobelx : public artist {
public:
  sobelx(int, int, const std::vector<int> &);
  char mapper(int, int);
};
