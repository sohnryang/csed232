#include "sobely.hpp"

#include <cmath>

void sobely::calculate_diff_y(const artist *art,
                              std::vector<std::vector<int>> &diff_y) {
  for (int y = 1; y < art->get_height(); y++) {
    diff_y.push_back({});
    for (int x = 0; x < art->get_width(); x++)
      diff_y.back().push_back(
          abs(art->pixel_at(x, y - 1) - art->pixel_at(x, y)));
  }
  diff_y.push_back({});
  diff_y.back().assign(diff_y[0].size(), 0);
}

sobely::sobely(int width, int height, const std::vector<int> &image_data)
    : artist(width, height, image_data) {
  calculate_diff_y(this, diff_y);
}

char sobely::mapper(int x, int y) {
  if (diff_y[y][x] >= 50)
    return '-';
  return ' ';
}
