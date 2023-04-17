#pragma once

#include <vector>

class artist {
protected:
  int width, height;
  std::vector<std::vector<int>> image;

public:
  artist(int, int, const std::vector<int> &);
  int pixel_at(int, int) const;
  virtual char mapper(int, int) = 0;
};
