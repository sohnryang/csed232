#pragma once

#include "artist.hpp"

#include <string>
#include <vector>

class iclassic : public artist {
public:
  static const std::string pattern; // constant for ascii art pattern.

  // Constructor of `iclassic`.
  iclassic(int width, int height, const std::vector<int> &image_data);

  // Get character of ascii art at a given x, y coordinates.
  char mapper(int x, int y);
};
