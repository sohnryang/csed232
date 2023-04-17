#include "iclassic.hpp"
#include "classic.hpp"

const std::string iclassic::pattern(classic::pattern.rbegin(),
                                    classic::pattern.rend());

iclassic::iclassic(int width, int height, const std::vector<int> &image_data)
    : artist(width, height, image_data) {}

char iclassic::mapper(int x, int y) {
  int pixel_value = pixel_at(x, y);
  return pattern[std::min(pixel_value / 17, 14)];
}
