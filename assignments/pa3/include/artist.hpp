#pragma once

#include <vector>

class artist {
private:
  int width, height;
  std::vector<std::vector<int>> image;

public:
  artist(int width, int height, const std::vector<int> &image_data);
  int get_width() const;
  int get_height() const;
  int pixel_at(int x, int y) const;
  virtual char mapper(int x, int y) = 0;
};
