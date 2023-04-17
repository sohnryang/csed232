#include "drawer.hpp"
#include "artist.hpp"

drawer::drawer(artist *art) : art(art) {}

artist *drawer::get_artist() const { return art; }

std::string drawer::draw() {
  std::string result;
  for (int y = 0; y < art->get_height(); y++) {
    for (int x = 0; x < art->get_width(); x++)
      result += art->mapper(x, y);
    result += '\n';
  }
  return result;
}
