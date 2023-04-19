#include "drawer.hpp"
#include "artist.hpp"

drawer::drawer(artist *art) : art(art) {}

artist *drawer::get_artist() const { return art; }

std::string drawer::draw() {
  std::string result; // result string

  // Loop over every pixel of the image.
  for (int y = 0; y < art->get_height(); y++) {
    for (int x = 0; x < art->get_width(); x++)
      // Map the pixel value to a character and add it to the result string.
      result += art->mapper(x, y);

    // Add newline character to the result string after every row.
    result += '\n';
  }
  return result;
}
