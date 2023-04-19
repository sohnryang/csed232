#pragma once

#include "artist.hpp"

#include <vector>

class gradient : public artist {
private:
  std::vector<std::vector<int>> diff_x; // difference matrix in x direction
  std::vector<std::vector<int>> diff_y; // difference matrix in y direction

public:
  // Constructor for `gradient`.
  gradient(int width, int height, const std::vector<int> &image_data);

  // Get character of ascii art at a given x, y coordinates.
  char mapper(int x, int y);
};
