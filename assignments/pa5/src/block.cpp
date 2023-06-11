#include "src/block.h"

Block::Block(int power) : power(power) {}

bool Block::operator==(const Block &rhs) const {
  return this->power == rhs.power; // compare between powers
}

bool Block::operator!=(const Block &rhs) const {
  return this->power != rhs.power; // compare between powers
}

int Block::get_power() const { return power; }
