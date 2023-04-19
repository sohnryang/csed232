#pragma once

#include "artist.hpp"

#include <string>
#include <vector>

class classic : public artist {
public:
  static const std::string pattern;
  classic(int width, int height, const std::vector<int> &image_data);
  char mapper(int x, int y);
};
