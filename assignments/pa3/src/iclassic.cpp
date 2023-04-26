#include "iclassic.hpp"
#include "classic.hpp"

#include <algorithm>
#include <string>
#include <vector>

// Initialize pattern for `iclassic` using pattern from `classic`.
const std::string iclassic::pattern(classic::pattern.rbegin(),
                                    classic::pattern.rend());

iclassic::iclassic(int width, int height, const std::vector<int> &image_data)
    : artist(width, height, image_data) {}

char iclassic::mapper(int x, int y) {
  int pixel_value = pixel_at(x, y); // get the pixel value at (x, y)

  // Map the pixel value to a character from the pattern string based on its
  // intensity level.
  return pattern[std::min(pixel_value / 17, 14)];
}
