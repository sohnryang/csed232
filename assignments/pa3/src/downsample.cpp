#include "downsample.hpp"

downsample::downsample(artist *art) : drawer(art), sc(art, -2, -2) {}

std::string downsample::draw() { return sc.draw(); }
