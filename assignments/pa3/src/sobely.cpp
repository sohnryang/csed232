#include "sobely.hpp"

void calculate_diff_y(const std::vector<std::vector<int>> &image,
                      std::vector<std::vector<int>> &diff_y) {
  for (int y = 1; y < image.size(); y++) {
    diff_y.push_back({});
    for (int x = 0; x < image[y].size(); x++)
      diff_y.back().push_back(abs(image[y - 1][x] - image[y][x]));
  }
  diff_y.push_back({});
  diff_y.back().assign(diff_y[0].size(), 0);
}

sobely::sobely(int width, int height, const std::vector<int> &image_data)
    : artist(width, height, image_data) {
  calculate_diff_y(image, diff_y);
}

char sobely::mapper(int x, int y) {
  if (diff_y[y][x] >= 50)
    return '-';
  return ' ';
}
