#include "scale.hpp"
#include "artist.hpp"

#include <string>

scale::scale(artist *art, int scale_x, int scale_y) : drawer(art) {
  if (scale_y < 0) { // if the y-scaling factor is negative
    repeat_y = 1;
    // Set `step_y` to the absolute value of the y-scaling factor.
    step_y = -scale_y;
  } else {
    repeat_y = scale_y; // set `repeat_y` to the y-scaling factor
    step_y = 1;
  }
  if (scale_x < 0) { // if the x-scaling factor is negative
    repeat_x = 1;
    // Set `step_x` to the absolute value of the x-scaling factor.
    step_x = -scale_x;
  } else {
    repeat_x = scale_x; // set `repeat_x` to the x-scaling factor
    step_x = 1;
  }
}

std::string scale::draw() {
  std::string res;
  // Loop through each y-coordinate of the scaled image.
  for (int y = 0; y < get_artist()->get_height(); y += step_y) {
    std::string line;
    // Loop through each x-coordinate of the scaled image.
    for (int x = 0; x < get_artist()->get_width(); x += step_x)
      // Loop through the `repeat_x` value to repeat the pixel horizontally.
      for (int rx = 0; rx < repeat_x; rx++)
        line += get_artist()->mapper(x, y); // add mapped character
    line += '\n'; // add a new line character at the end of the line
    // Loop through the `repeat_y` value to repeat the line vertically.
    for (int ry = 0; ry < repeat_y; ry++)
      res += line; // add the line to the result string
  }
  return res;
}
