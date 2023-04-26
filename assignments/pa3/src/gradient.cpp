#include "gradient.hpp"
#include "sobelx.hpp"
#include "sobely.hpp"

#include <vector>

gradient::gradient(int width, int height, const std::vector<int> &image_data)
    : artist(width, height, image_data) {
  // Calculate x and y differences using sobel filter.
  sobelx::calculate_diff_x(this, diff_x);
  sobely::calculate_diff_y(this, diff_y);
}

char gradient::mapper(int x, int y) {
  // Determine the character to map the pixel value to based on the x and y
  // differences.
  if (diff_x[y][x] >= 50 && diff_y[y][x] >= 50)
    return '+';
  else if (diff_x[y][x] >= 50)
    return '|';
  else if (diff_y[y][x] >= 50)
    return '-';
  return ' ';
}
