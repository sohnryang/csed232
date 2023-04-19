#pragma once

#include "drawer.hpp"
#include "scale.hpp"

#include <string>

class upsample : public drawer {
private:
  scale sc; // scale object for upsample calculation

public:
  // Constructor for `upsample`.
  upsample(artist *art);

  // Draw upsampled image.
  std::string draw();
};
