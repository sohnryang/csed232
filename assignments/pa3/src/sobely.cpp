#include "sobely.hpp"

sobely::sobely(int width, int height, const std::vector<int> &image_data)
    : artist(width, height, image_data) {}

char sobely::mapper(int, int) {}
