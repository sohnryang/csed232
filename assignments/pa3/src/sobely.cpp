#include "sobely.hpp"

sobely::sobely(int width, int height, const std::vector<int> &image_data)
    : artist(width, height, image_data) {
  for (int y = 1; y < height; y++) {
    diff_y.push_back({});
    for (int x = 0; x < width; x++)
      diff_y.back().push_back(abs(image[y - 1][x] - image[y][x]));
  }
  diff_y.push_back({});
  diff_y.back().assign(width, 0);
}

char sobely::mapper(int x, int y) {
  if (diff_y[y][x] >= 50)
    return '-';
  return ' ';
}
