#include "scale.hpp"
#include "artist.hpp"

scale::scale(artist *art, int scale_x, int scale_y) : drawer(art) {
  if (scale_y < 0) {
    repeat_y = 1;
    step_y = -scale_y;
  } else {
    repeat_y = scale_y;
    step_y = 1;
  }
  if (scale_x < 0) {
    repeat_x = 1;
    step_x = -scale_x;
  } else {
    repeat_x = scale_x;
    step_x = 1;
  }
}

std::string scale::draw() {
  std::string res;
  for (int y = 0; y < get_artist()->get_height(); y += step_y) {
    std::string line;
    for (int x = 0; x < get_artist()->get_width(); x += step_x)
      for (int rx = 0; rx < repeat_x; rx++)
        line += get_artist()->mapper(x, y);
    line += '\n';
    for (int ry = 0; ry < repeat_y; ry++)
      res += line;
  }
  return res;
}
