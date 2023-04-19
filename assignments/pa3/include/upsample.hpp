#pragma once

#include "drawer.hpp"
#include "scale.hpp"

#include <string>

class upsample : public drawer {
private:
  scale sc;

public:
  upsample(artist *art);
  std::string draw();
};
