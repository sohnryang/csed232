#pragma once

#include "artist.hpp"

#include <string>

class drawer {
public:
  drawer(artist *);
  virtual std::string draw();
};
