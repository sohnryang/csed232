#pragma once

#include "artist.hpp"

#include <vector>

class sobely : public artist {
public:
  sobely(int, int, const std::vector<int> &);
  char mapper(int, int);
};
