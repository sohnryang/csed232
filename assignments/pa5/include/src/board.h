#pragma once

#include "block.h"

#include <array>
#include <optional>
#include <random>
#include <utility>
#include <vector>

// Single entry of the board.
using BoardEntry = std::optional<Block>;

// Single row of the board.
using BoardRow = std::array<BoardEntry, 4>;

// Board matrix type.
using BoardMatrix = std::array<BoardRow, 4>;

enum class InputKind { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };

class Board {
private:
  // 4 by 4 matrix for board.
  BoardMatrix board_matrix;

public:
  // Default constructor.
  Board() = default;

  // Constructor with given board matrix.
  Board(BoardMatrix board_matrix);

  // Copy constructor.
  Board(const Board &that) = default;

  // Copy assignment operator.
  Board &operator=(const Board &that) = default;

  // Index operator.
  BoardEntry &operator[](std::pair<int, int> pos);

  // Index operator, const version.
  const BoardEntry &operator[](std::pair<int, int> pos) const;

  // Getter for specific row.
  std::vector<BoardEntry> row_at(int index) const;

  // Getter for specific column.
  std::vector<BoardEntry> column_at(int index) const;

  // Getter for board matrix.
  BoardMatrix get_board_matrix() const;

  // Static method for reducing a line.
  static std::pair<std::vector<Block>, std::vector<std::pair<Block, int>>>
  reduce_line(const std::vector<BoardEntry> &line);

  // Static method for checking if line can be reduced.
  static bool is_reducible(const std::vector<BoardEntry> &line);

  // Get vacant positions.
  std::vector<std::pair<int, int>> vacant_pos() const;

  // Check if board can be movable.
  bool check_movable() const;

  // Check if game is finished.
  bool is_finished() const;

  // Check if the given input produces an effective move.
  bool is_effective_move(InputKind input) const;

  // Move the board in given direction and return created blocks.
  std::vector<std::pair<Block, std::pair<int, int>>>
  move_board(InputKind input);
};
