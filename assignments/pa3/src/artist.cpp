#include "artist.hpp"

#include <algorithm>
#include <iterator>

artist::artist(int width, int height, const std::vector<int> &image_data)
    : width(width), height(height) {
  image.assign(height, {});
  for (int y = 0; y < height; y++) {
    int copy_start = 2 + y * width;
    std::copy_n(image_data.begin() + copy_start, width,
                std::back_inserter(image[y]));
  }
}

int artist::pixel_at(int x, int y) { return image[y][x]; }
