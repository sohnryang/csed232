#pragma once

#include "artist.hpp"

#include <vector>

class sobelx : public artist {
private:
  std::vector<std::vector<int>> diff_x;

public:
  sobelx(int width, int height, const std::vector<int> &image_data);
  char mapper(int x, int y);
  static void calculate_diff_x(const artist *art,
                               std::vector<std::vector<int>> &diff_x);
};
