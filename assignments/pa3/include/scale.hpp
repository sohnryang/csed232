#pragma once

#include "artist.hpp"
#include "drawer.hpp"

#include <string>

class scale : public drawer {
public:
  scale(artist *, int, int);
  std::string draw();
};
