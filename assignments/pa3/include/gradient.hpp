#pragma once

#include <artist.hpp>

#include <vector>

class gradient : public artist {
public:
  gradient(int, int, const std::vector<int> &);
  char mapper(int, int);
};
