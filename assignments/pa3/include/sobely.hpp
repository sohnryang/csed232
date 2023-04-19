#pragma once

#include "artist.hpp"

#include <vector>

class sobely : public artist {
private:
  std::vector<std::vector<int>> diff_y; // difference matrix in y direction

public:
  // Constructor for `sobely`
  sobely(int width, int height, const std::vector<int> &image_data);

  // Get character of ascii art at a given x, y coordinates.
  char mapper(int x, int y);

  // Calculate difference matrix in y direction of image saved in `art` and save
  // it to `diff_y`.
  static void calculate_diff_y(const artist *art,
                               std::vector<std::vector<int>> &diff_y);
};
