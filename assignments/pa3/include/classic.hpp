#pragma once

#include "artist.hpp"

#include <string>
#include <vector>

class classic : public artist {
public:
  static const std::string pattern;
  classic(int, int, const std::vector<int> &);
  char mapper(int, int);
};
