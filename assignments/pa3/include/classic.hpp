#pragma once

#include <artist.hpp>

#include <vector>

class classic : public artist {
public:
  classic(int, int, const std::vector<int> &);
  char mapper(int, int);
};
