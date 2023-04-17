#pragma once

#include "artist.hpp"

#include <vector>

class sobely : public artist {
private:
  std::vector<std::vector<int>> diff_y;

public:
  sobely(int, int, const std::vector<int> &);
  char mapper(int, int);
};
