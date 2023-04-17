#include "sobelx.hpp"

#include <algorithm>

sobelx::sobelx(int width, int height, const std::vector<int> &image_data)
    : artist(width, height, image_data) {
  for (auto &line : image) {
    diff_x.push_back({});
    for (int i = 1; i < line.size(); i++)
      diff_x.back().push_back(abs(line[i] - line[i - 1]));
    diff_x.back().push_back(0);
  }
}

char sobelx::mapper(int x, int y) {
  if (diff_x[y][x] >= 50)
    return '|';
  return ' ';
}
