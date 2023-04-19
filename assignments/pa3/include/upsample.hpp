#pragma once

#include "drawer.hpp"

#include <string>

class upsample : public drawer {
public:
  upsample(artist *art);
  std::string draw();
};
