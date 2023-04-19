#pragma once

#include "artist.hpp"

#include <string>
#include <vector>

class iclassic : public artist {
public:
  static const std::string pattern;
  iclassic(int width, int height, const std::vector<int> &image_data);
  char mapper(int x, int y);
};
