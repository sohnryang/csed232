#pragma once

#include "drawer.hpp"
#include "scale.hpp"

#include <string>

class downsample : public drawer {
private:
  scale sc;

public:
  downsample(artist *art);
  std::string draw();
};
