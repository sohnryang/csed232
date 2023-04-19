#include "downsample.hpp"

// Since downsample is a special case of scale, we can use that object.
downsample::downsample(artist *art) : drawer(art), sc(art, -2, -2) {}

std::string downsample::draw() { return sc.draw(); }
