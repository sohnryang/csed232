#include "sobelx.hpp"

sobelx::sobelx(int width, int height, const std::vector<int> &image_data)
    : artist(width, height, image_data) {}

char sobelx::mapper(int, int) {}
