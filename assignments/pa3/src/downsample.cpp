#include "downsample.hpp"
#include "artist.hpp"

#include <string>

// Since downsample is a special case of scale, we can use that object.
downsample::downsample(artist *art) : drawer(art) {}

std::string downsample::draw() {
  std::string res;
  // Loop through each y-coordinate of the scaled image.
  for (int y = 0; y < get_artist()->get_height(); y += 2) {
    std::string line;
    // Loop through each x-coordinate of the scaled image.
    for (int x = 0; x < get_artist()->get_width(); x += 2)
      line += get_artist()->mapper(x, y); // add mapped character
    line += '\n'; // add a new line character at the end of the line
    res += line;  // add the line to the result string
  }
  return res;
}
