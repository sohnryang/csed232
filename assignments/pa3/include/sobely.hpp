#pragma once

#include "artist.hpp"

#include <vector>

void calculate_diff_y(const std::vector<std::vector<int>> &,
                      std::vector<std::vector<int>> &);

class sobely : public artist {
private:
  std::vector<std::vector<int>> diff_y;

public:
  sobely(int, int, const std::vector<int> &);
  char mapper(int, int);
};
