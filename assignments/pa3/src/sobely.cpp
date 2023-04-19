#include "sobely.hpp"

#include <cmath>

void sobely::calculate_diff_y(const artist *art,
                              std::vector<std::vector<int>> &diff_y) {
  // Loop through every row of pixels, except the first one.
  for (int y = 1; y < art->get_height(); y++) {
    diff_y.push_back({}); // add a new row to the `diff_y` 2D vector
    for (int x = 0; x < art->get_width(); x++)
      // Calculate the difference between the current pixel and the pixel above.
      diff_y.back().push_back(
          abs(art->pixel_at(x, y - 1) - art->pixel_at(x, y)));
  }
  diff_y.push_back({});                      // add an empty row to `diff_y`
  diff_y.back().assign(diff_y[0].size(), 0); // fill the row with zeros
}

sobely::sobely(int width, int height, const std::vector<int> &image_data)
    : artist(width, height, image_data) {
  // Call the `calculate_diff_y` function to calculate the horizontal intensity
  // gradient of the image.
  calculate_diff_y(this, diff_y);
}

char sobely::mapper(int x, int y) {
  // If the intensity gradient at (x, y) is greater than or equal to 50, return
  // '-', else return ' '.
  if (diff_y[y][x] >= 50)
    return '-';
  return ' ';
}
