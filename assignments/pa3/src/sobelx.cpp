#include "sobelx.hpp"

void calculate_diff_x(const artist *art,
                      std::vector<std::vector<int>> &diff_x) {
  for (int y = 0; y < art->get_height(); y++) {
    diff_x.push_back({});
    for (int x = 1; x < art->get_width(); x++)
      diff_x.back().push_back(
          abs(art->pixel_at(x, y) - art->pixel_at(x - 1, y)));
    diff_x.back().push_back(0);
  }
}

sobelx::sobelx(int width, int height, const std::vector<int> &image_data)
    : artist(width, height, image_data) {
  calculate_diff_x(this, diff_x);
}

char sobelx::mapper(int x, int y) {
  if (diff_x[y][x] >= 50)
    return '|';
  return ' ';
}
