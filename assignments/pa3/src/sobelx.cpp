#include "sobelx.hpp"
#include "artist.hpp"

#include <cmath>
#include <vector>

void sobelx::calculate_diff_x(const artist *art,
                              std::vector<std::vector<int>> &diff_x) {
  // Loop through every row of pixels.
  for (int y = 0; y < art->get_height(); y++) {
    diff_x.push_back({}); // add a new row to the `diff_x` 2D vector
    // Loop through every column of pixels.
    for (int x = 1; x < art->get_width(); x++)
      // Calculate the difference between the current pixel and the previous
      // pixel.
      diff_x.back().push_back(
          abs(art->pixel_at(x, y) - art->pixel_at(x - 1, y)));
    // Add a zero to the end of the current row.
    diff_x.back().push_back(0);
  }
}

sobelx::sobelx(int width, int height, const std::vector<int> &image_data)
    : artist(width, height, image_data) {
  // Call the `calculate_diff_x` function to calculate the horizontal intensity
  // gradient of the image.
  calculate_diff_x(this, diff_x);
}

char sobelx::mapper(int x, int y) {
  // If the intensity gradient at (x, y) is greater than or equal to 50, return
  // '|', else return ' '.
  if (diff_x[y][x] >= 50)
    return '|';
  return ' ';
}
