#pragma once

#include "artist.hpp"

#include <vector>

class iclassic : public artist {
public:
  iclassic(int, int, std::vector<int>);
  char mapper(int, int);
};
