#include "downsample.hpp"

downsample::downsample(artist *art) : drawer(art) {}

std::string downsample::draw() {
  std::string res;
  for (int y = 0; y < get_artist()->get_height(); y += 2) {
    for (int x = 0; x < get_artist()->get_width(); x += 2)
      res += get_artist()->mapper(x, y);
    res += '\n';
  }
  return res;
}
