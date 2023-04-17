#pragma once

#include <vector>

class artist {
private:
  int width, height;
  std::vector<std::vector<int>> image;

public:
  artist(int, int, const std::vector<int> &);
  int get_width() const;
  int get_height() const;
  int pixel_at(int, int) const;
  virtual char mapper(int, int) = 0;
};
