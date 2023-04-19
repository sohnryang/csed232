#pragma once

#include "artist.hpp"

#include <vector>

class sobely : public artist {
private:
  std::vector<std::vector<int>> diff_y;

public:
  sobely(int width, int height, const std::vector<int> &image_data);
  char mapper(int x, int y);
  static void calculate_diff_y(const artist *art,
                               std::vector<std::vector<int>> &diff_y);
};
