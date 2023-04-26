#pragma once

#include "drawer.hpp"
#include "scale.hpp"

#include <string>

class downsample : public drawer {
public:
  // Constructor for `downsample`.
  downsample(artist *art);

  // Draw downsampled image.
  std::string draw();
};
