#pragma once

#include "artist.hpp"
#include <vector>

class binary : public artist {
public:
  binary(int width, int height, const std::vector<int> &image_data);
  char mapper(int x, int y);
};
