#pragma once

#include "artist.hpp"
#include "drawer.hpp"

#include <string>

class scale : public drawer {
private:
  int repeat_x; // number of characters to repeat in x direction
  int step_x;   // number of steps to take in x direction
  int repeat_y; // number of characters to repeat in y direction
  int step_y;   // number of steps to take in y direction

public:
  // Constructor of `scale`.
  scale(artist *art, int scale_x, int scale_y);

  // Create scaled ascii art string using artist.
  std::string draw();
};
