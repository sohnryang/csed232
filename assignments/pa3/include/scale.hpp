#pragma once

#include "artist.hpp"
#include "drawer.hpp"

#include <string>

class scale : public drawer {
private:
  int repeat_x, step_x, repeat_y, step_y;

public:
  scale(artist *art, int scale_x, int scale_y);
  std::string draw();
};
