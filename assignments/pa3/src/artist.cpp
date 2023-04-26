#include "artist.hpp"

#include <algorithm>
#include <iterator>

artist::artist(int width, int height, const std::vector<int> &image_data)
    : width(width), height(height) {
  image.assign(height, {}); // assign empty rows to image vector

  for (int y = 0; y < height; y++) { // copy image_data into image vector
    // calculate the starting index of image_data for copying
    int copy_start = y * width;

    // copy 'width' number of elements from image_data to image[y]
    std::copy_n(image_data.begin() + copy_start, width,
                std::back_inserter(image[y]));
  }
}

artist::~artist() {}

int artist::get_width() const { return width; }

int artist::get_height() const { return height; }

int artist::pixel_at(int x, int y) const { return image[y][x]; }
