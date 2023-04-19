#pragma once

#include "artist.hpp"

#include <string>

class drawer {
private:
  artist *art;

protected:
  artist *get_artist() const;

public:
  drawer(artist *art);
  virtual std::string draw();
};
