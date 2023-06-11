#pragma once

#include <optional>

class Block {
private:
  // Exponent for block.
  int power;

public:
  // Default constructor.
  Block() = default;

  // Constructor with power given.
  Block(int power);

  // Copy constructor.
  Block(const Block &that) = default;

  // Copy assignment operator.
  Block &operator=(const Block &that) = default;

  // Equality operator.
  bool operator==(const Block &rhs) const;

  // Non-equality operator.
  bool operator!=(const Block &rhs) const;

  // Getter for power.
  int get_power() const;
};
