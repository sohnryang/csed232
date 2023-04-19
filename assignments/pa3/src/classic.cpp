#include "classic.hpp"

#include <algorithm>

const std::string classic::pattern = "@&%WXAHOT*^+-. ";

classic::classic(int width, int height, const std::vector<int> &image_data)
    : artist(width, height, image_data) {}

char classic::mapper(int x, int y) {
  int pixel_value = pixel_at(x, y); // obtain the pixel value at (x, y)

  // Map the pixel value to a character from the pattern string based on its
  // intensity level.
  return pattern[std::min(pixel_value / 17, 14)];
}
