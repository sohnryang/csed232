#include "upsample.hpp"
#include "artist.hpp"

upsample::upsample(artist *art) : drawer(art), sc(art, 2, 2) {}

std::string upsample::draw() { return sc.draw(); }
