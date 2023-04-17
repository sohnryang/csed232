#include "gradient.hpp"

gradient::gradient(int width, int height, const std::vector<int> &image_data)
    : artist(width, height, image_data) {}

char gradient::mapper(int, int) {}
