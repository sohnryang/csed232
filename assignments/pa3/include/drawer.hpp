#pragma once

#include "artist.hpp"

#include <string>

class drawer {
private:
  artist *art; // pointer to artist.

protected:
  // Getter for artist pointer.
  artist *get_artist() const;

public:
  // Constructor for `drawer`.
  drawer(artist *art);

  // Destructor for `artist`.
  virtual ~drawer();

  // Create ascii art string using artist.
  virtual std::string draw();
};
