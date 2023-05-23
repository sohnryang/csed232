#pragma once

#include "block.h"

#include <array>
#include <optional>
#include <random>
#include <utility>
#include <vector>

using BoardEntry = std::optional<Block>;
using BoardRow = std::array<BoardEntry, 4>;
using BoardMatrix = std::array<BoardRow, 4>;

enum class InputKind { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };

class Board {
private:
  BoardMatrix board_matrix;

public:
  Board() = default;
  Board(BoardMatrix board_matrix);
  Board(const Board &that) = default;

  Board &operator=(const Board &that) = default;
  BoardEntry &operator[](std::pair<int, int> pos);
  const BoardEntry &operator[](std::pair<int, int> pos) const;

  std::vector<BoardEntry> row_at(int index) const;
  std::vector<BoardEntry> column_at(int index) const;
  BoardMatrix get_board_matrix() const;

  static std::pair<std::vector<Block>, std::vector<std::pair<Block, int>>>
  reduce_line(const std::vector<BoardEntry> &line);
  static bool is_reducible(const std::vector<BoardEntry> &line);

  std::vector<std::pair<int, int>> vacant_pos() const;
  bool check_movable() const;
  bool is_finished() const;
  bool is_effective_move(InputKind input) const;
  std::vector<std::pair<Block, std::pair<int, int>>>
  move_board(InputKind input);
};
