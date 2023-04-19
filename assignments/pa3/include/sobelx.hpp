#pragma once

#include "artist.hpp"

#include <vector>

class sobelx : public artist {
private:
  std::vector<std::vector<int>> diff_x; // difference matrix in x direction

public:
  // Constructor for `sobelx`.
  sobelx(int width, int height, const std::vector<int> &image_data);

  // Get character of ascii art at a given x, y coordinates.
  char mapper(int x, int y);

  // Calculate difference matrix in x direction of image saved in `art` and save
  // it to `diff_x`.
  static void calculate_diff_x(const artist *art,
                               std::vector<std::vector<int>> &diff_x);
};
