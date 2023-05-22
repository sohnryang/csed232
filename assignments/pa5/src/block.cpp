#include "block.h"

Block::Block() : Block(1) {}

Block::Block(int power) : power(power) {}

Block::Block(const Block &that) : Block(that.power) {}

bool Block::operator==(const Block &rhs) const {
  return this->power == rhs.power;
}

bool Block::operator!=(const Block &rhs) const {
  return this->power != rhs.power;
}

int Block::get_power() const { return power; }
