#pragma once

#include "drawer.hpp"

#include <string>

class downsample : public drawer {
public:
  downsample(artist *);
  std::string draw();
};
