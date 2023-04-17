#pragma once

#include "artist.hpp"

#include <string>
#include <vector>

class iclassic : public artist {
public:
  static const std::string pattern;
  iclassic(int, int, const std::vector<int> &);
  char mapper(int, int);
};
