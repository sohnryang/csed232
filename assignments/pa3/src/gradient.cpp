#include "gradient.hpp"
#include "sobelx.hpp"
#include "sobely.hpp"

gradient::gradient(int width, int height, const std::vector<int> &image_data)
    : artist(width, height, image_data) {
  calculate_diff_x(image, diff_x);
  calculate_diff_y(image, diff_y);
}

char gradient::mapper(int x, int y) {
  if (diff_x[y][x] >= 50 && diff_y[y][x] >= 50)
    return '+';
  else if (diff_x[y][x] >= 50)
    return '|';
  else if (diff_y[y][x] >= 50)
    return '-';
  return ' ';
}
