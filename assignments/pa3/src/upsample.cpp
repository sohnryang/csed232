#include "upsample.hpp"
#include "artist.hpp"

upsample::upsample(artist *art) : drawer(art) {}

std::string upsample::draw() {
  std::string res;
  for (int y = 0; y < get_artist()->get_height(); y++) {
    std::string line;
    for (int x = 0; x < get_artist()->get_width(); x++)
      line += std::string(2, get_artist()->mapper(x, y));
    line += '\n';
    res += line + line;
  }
  return res;
}
