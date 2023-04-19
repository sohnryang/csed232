#include "upsample.hpp"
#include "artist.hpp"

// Since upsample is a special case of scale, we can use that object.
upsample::upsample(artist *art) : drawer(art), sc(art, 2, 2) {}

std::string upsample::draw() { return sc.draw(); }
