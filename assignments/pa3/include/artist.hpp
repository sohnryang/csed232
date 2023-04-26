#pragma once

#include <vector>

class artist {
private:
  int width;  // width of image
  int height; // height of image

  // image stored in 2D vector, in row-major order
  std::vector<std::vector<int>> image;

public:
  // Constructor of `artist`.
  artist(int width, int height, const std::vector<int> &image_data);

  // Destructor of `artist`.
  virtual ~artist();

  // Get the width of the image.
  int get_width() const;

  // Get the height of the image.
  int get_height() const;

  // Get the pixel value at a given x, y coordinates.
  int pixel_at(int x, int y) const;

  // Pure virtual function for mapper.
  virtual char mapper(int x, int y) = 0;
};
