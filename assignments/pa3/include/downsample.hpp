#pragma once

#include "drawer.hpp"
#include "scale.hpp"

#include <string>

class downsample : public drawer {
private:
  scale sc; // scale object for downsample calculation

public:
  // Constructor for `downsample`.
  downsample(artist *art);

  // Draw downsampled image.
  std::string draw();
};
