#pragma once

#include "drawer.hpp"
#include "scale.hpp"

#include <string>

class upsample : public drawer {
public:
  // Constructor for `upsample`.
  upsample(artist *art);

  // Draw upsampled image.
  std::string draw();
};
