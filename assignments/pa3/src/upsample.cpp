#include "upsample.hpp"
#include "artist.hpp"

#include <string>

// Since upsample is a special case of scale, we can use that object.
upsample::upsample(artist *art) : drawer(art) {}

std::string upsample::draw() {
  std::string res;
  // Loop through each y-coordinate of the scaled image.
  for (int y = 0; y < get_artist()->get_height(); y++) {
    std::string line;
    // Loop through each x-coordinate of the scaled image.
    for (int x = 0; x < get_artist()->get_width(); x++)
      // Loop through the `repeat_x` value to repeat the pixel horizontally.
      for (int rx = 0; rx < 2; rx++)
        line += get_artist()->mapper(x, y); // add mapped character
    line += '\n'; // add a new line character at the end of the line
    // Loop through the `repeat_y` value to repeat the line vertically.
    for (int ry = 0; ry < 2; ry++)
      res += line; // add the line to the result string
  }
  return res;
}
