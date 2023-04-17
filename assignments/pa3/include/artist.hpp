#pragma once

#include <vector>

class artist {
public:
  artist(int, int, const std::vector<int> &);
  virtual char mapper(int, int);
};
