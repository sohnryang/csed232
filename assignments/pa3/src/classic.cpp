#include "classic.hpp"

#include <algorithm>

const std::string classic::pattern = "@&%WXAHOT*^+-. ";

classic::classic(int width, int height, const std::vector<int> &image_data)
    : artist(width, height, image_data) {}

char classic::mapper(int x, int y) {
  int pixel_value = pixel_at(x, y);
  return pattern[std::min(pixel_value / 17, 14)];
}
