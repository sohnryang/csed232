#include "binary.hpp"
#include "artist.hpp"

#include <vector>

binary::binary(int width, int height, const std::vector<int> &image_data)
    : artist(width, height, image_data) {}

char binary::mapper(int x, int y) { return pixel_at(x, y) >= 80 ? '#' : ' '; }
