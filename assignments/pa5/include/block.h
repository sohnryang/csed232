#pragma once

#include <optional>

class Block {
private:
  int power;

public:
  Block();
  Block(int power);
  Block(const Block &that);

  Block &operator=(const Block &that) = default;
  bool operator==(const Block &rhs) const;
  bool operator!=(const Block &rhs) const;

  int get_power() const;
};
