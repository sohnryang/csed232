#pragma once

#include <optional>

class Block {
private:
  int power;

public:
  Block() = default;
  Block(int power);
  Block(const Block &that) = default;

  Block &operator=(const Block &that) = default;
  bool operator==(const Block &rhs) const;
  bool operator!=(const Block &rhs) const;

  int get_power() const;
};
