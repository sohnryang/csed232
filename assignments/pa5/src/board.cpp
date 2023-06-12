#include "src/board.h"
#include "src/block.h"

#include <algorithm>
#include <iterator>
#include <optional>
#include <random>
#include <utility>
#include <vector>

Board::Board(BoardMatrix board_matrix) : board_matrix(board_matrix) {}

BoardEntry &Board::operator[](std::pair<int, int> pos) {
  return board_matrix[pos.first][pos.second];
}

const BoardEntry &Board::operator[](std::pair<int, int> pos) const {
  return board_matrix[pos.first][pos.second];
}

std::vector<std::pair<int, int>> Board::vacant_pos() const {
  std::vector<std::pair<int, int>> res;
  for (int y = 0; y < 4; y++)
    for (int x = 0; x < 4; x++)
      if (!board_matrix[y][x].has_value()) // if current position is vacant
        res.push_back({y, x});             // push to the result
  return res;
}

std::vector<BoardEntry> Board::row_at(int index) const {
  return {board_matrix[index].begin(), board_matrix[index].end()};
}

std::vector<BoardEntry> Board::column_at(int index) const {
  std::vector<std::optional<Block>> col; // resulting column
  std::transform(board_matrix.begin(), board_matrix.end(),
                 std::back_inserter(col),
                 [index](auto row) { return row[index]; });
  return col;
}

BoardMatrix Board::get_board_matrix() const { return board_matrix; }

std::pair<std::vector<Block>, std::vector<std::pair<Block, int>>>
Board::reduce_line(const std::vector<BoardEntry> &line) {
  std::vector<Block> res; // result
  // Created blocks and their indices.
  std::vector<std::pair<Block, int>> created_blocks;
  BoardEntry last; // last entry before it is pushed
  for (const auto &entry : line) {
    if (!entry.has_value())
      continue;
    if (!last.has_value()) {
      last = entry;
      continue;
    }
    if (last == entry) {
      Block new_block = last.value().get_power() + 1;    // create a new block
      created_blocks.push_back({new_block, res.size()}); // record its index
      res.push_back(new_block); // push created block to result
      last.reset();             // set last to 'none' state
      continue;
    }
    res.push_back(last.value()); // push last block to the result
    last = entry;                // set last block
  }
  if (last.has_value())
    res.push_back(last.value()); // push the leftover last block
  return {res, created_blocks};
}

bool Board::is_reducible(const std::vector<BoardEntry> &line) {
  auto reduced = reduce_line(line).first;
  for (int i = 0; i < reduced.size(); i++)
    if (reduced[i] != line[i]) // check if mismatch
      return true;
  return false;
}

bool Board::check_movable() const {
  for (int i = 0; i < 4; i++) {
    std::vector<BoardEntry> row = row_at(i), col = column_at(i), row_reversed,
                            col_reversed;
    // Save the reversed row and column to *_reversed variables.
    std::reverse_copy(row.begin(), row.end(), std::back_inserter(row_reversed));
    std::reverse_copy(col.begin(), col.end(), std::back_inserter(col_reversed));
    // Check if i'th row and column are reducable.
    if (is_reducible(row) || is_reducible(row_reversed) || is_reducible(col) ||
        is_reducible(col_reversed))
      return true;
  }
  return false;
}

bool Board::is_finished() const {
  // Empty board doesn't mean it's finished. (although that state cannot be
  // reached in regular variant of 2048)
  if (std::all_of(board_matrix.begin(), board_matrix.end(), [](const auto &r) {
        return std::none_of(r.begin(), r.end(),
                            [](const auto &v) { return v.has_value(); });
      }))
    return false;
  return !check_movable();
}

bool Board::is_effective_move(InputKind input) const {
  for (int i = 0; i < 4; i++) {
    // Line corresponding to the input.
    std::vector<BoardEntry> line;
    switch (input) {
    case InputKind::UP:
      line = column_at(i); // i'th column in up-to-down order
      break;
    case InputKind::DOWN:
      line = column_at(i);
      // Reverse to obtain i'th column in down-to-up order.
      std::reverse(line.begin(), line.end());
      break;
    case InputKind::LEFT:
      line = row_at(i); // i'th row in left-to-right order
      break;
    case InputKind::RIGHT:
      line = row_at(i);
      // Reverse to obtain i'th row in right-to-left order.
      std::reverse(line.begin(), line.end());
      break;
    }
    if (is_reducible(line))
      return true;
  }

  // The move is ineffective if all column/rows are irreducable in the given
  // direction.
  return false;
}

std::vector<std::pair<Block, std::pair<int, int>>>
Board::move_board(InputKind input) {
  int direction = 1; // 1 if up-to-down or left-to-right, -1 if otherwise
  std::vector<std::pair<Block, std::pair<int, int>>> created_blocks;
  if (input == InputKind::DOWN || input == InputKind::RIGHT)
    direction = -1; // set direction accordingly
  for (int i = 0; i < 4; i++) {
    std::vector<BoardEntry> line;

    // Fetch i'th column or row, depending on input.
    if (input == InputKind::UP || input == InputKind::DOWN)
      line = column_at(i);
    else
      line = row_at(i);
    // Reverse the line if needed.
    if (input == InputKind::DOWN || input == InputKind::RIGHT)
      std::reverse(line.begin(), line.end());

    // Reduce the line.
    auto [reduced, created_blocks_line] = reduce_line(line);
    // Create coordinates from indices in `created_blocks_line`.
    std::transform(
        created_blocks_line.begin(), created_blocks_line.end(),
        std::back_inserter(created_blocks),
        [&input, i](const auto &v) -> std::pair<Block, std::pair<int, int>> {
          const auto &[block, line_idx] = v;
          switch (input) {
          case InputKind::UP:
            return {block, {line_idx, i}};
          case InputKind::DOWN:
            return {block, {3 - line_idx, i}};
          case InputKind::LEFT:
            return {block, {i, line_idx}};
          case InputKind::RIGHT:
            return {block, {i, 3 - line_idx}};
          }
        });
    int empty_start = 0; // index where "empty" optionals start.
    // I know that this duplicated code looks awful, but there are not many
    // choices I can make...
    // Maybe we can just transpose the board and care only about UP/DOWN inputs
    if (input == InputKind::UP || input == InputKind::DOWN) {
      BoardMatrix::iterator it;
      if (input == InputKind::UP)
        it = board_matrix.begin();
      else
        it = board_matrix.begin() + 3;
      std::for_each(reduced.begin(), reduced.end(),
                    [&it, i, direction, &empty_start](const auto &v) {
                      (*it)[i] = v;
                      if (empty_start < 3)
                        it += direction; // this is why we are using `direction`
                      empty_start++;
                    });
      // Fill the rest with empty optionals.
      for (int j = empty_start; j < 4; j++) {
        (*it)[i] = {};
        if (j < 3)
          it += direction;
      }
    } else {
      BoardRow::iterator it;
      if (input == InputKind::LEFT)
        it = board_matrix[i].begin();
      else
        it = board_matrix[i].begin() + 3;
      std::for_each(reduced.begin(), reduced.end(),
                    [&it, direction, &empty_start](const auto &v) {
                      *it = v;
                      if (empty_start < 3)
                        it += direction; // this is why we are using `direction`
                      empty_start++;
                    });
      // Fill the rest with empty optionals.
      for (int j = empty_start; j < 4; j++) {
        *it = {};
        if (j < 3)
          it += direction;
      }
    }
  }

  // Sort created blocks by their positions.
  std::sort(
      created_blocks.begin(), created_blocks.end(),
      [](const auto &v1, const auto &v2) { return v1.second < v2.second; });
  return created_blocks;
}
