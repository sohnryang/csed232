#include "board.h"
#include "block.h"

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
      if (!board_matrix[y][x].has_value())
        res.push_back({y, x});
  return res;
}

std::vector<BoardEntry> Board::row_at(int index) const {
  return {board_matrix[index].begin(), board_matrix[index].end()};
}

std::vector<BoardEntry> Board::column_at(int index) const {
  std::vector<std::optional<Block>> col;
  std::transform(board_matrix.begin(), board_matrix.end(),
                 std::back_inserter(col),
                 [index](auto row) { return row[index]; });
  return col;
}

BoardMatrix Board::get_board_matrix() const { return board_matrix; }

std::pair<std::vector<Block>, std::vector<std::pair<Block, int>>>
Board::reduce_line(const std::vector<BoardEntry> &line) {
  std::vector<Block> res;
  std::vector<std::pair<Block, int>> created_blocks;
  BoardEntry last;
  for (const auto &entry : line) {
    if (!entry.has_value())
      continue;
    if (!last.has_value()) {
      last = entry;
      continue;
    }
    if (last == entry) {
      Block new_block = last.value().get_power() + 1;
      created_blocks.push_back({new_block, res.size()});
      res.push_back(new_block);
      last.reset();
      continue;
    }
    res.push_back(last.value());
    last = entry;
  }
  if (last.has_value())
    res.push_back(last.value());
  return {res, created_blocks};
}

bool Board::is_reducible(const std::vector<BoardEntry> &line) {
  auto compactified = reduce_line(line).first;
  for (int i = 0; i < compactified.size(); i++)
    if (compactified[i] != line[i])
      return true;
  return false;
}

bool Board::check_movable() const {
  for (int i = 0; i < 4; i++) {
    std::vector<BoardEntry> row = row_at(i), col = column_at(i), row_reversed,
                            col_reversed;
    std::reverse_copy(row.begin(), row.end(), std::back_inserter(row_reversed));
    std::reverse_copy(col.begin(), col.end(), std::back_inserter(col_reversed));
    if (is_reducible(row) || is_reducible(row_reversed) || is_reducible(col) ||
        is_reducible(col_reversed))
      return true;
  }
  return false;
}

bool Board::is_finished() const {
  if (std::all_of(board_matrix.begin(), board_matrix.end(), [](const auto &r) {
        return std::none_of(r.begin(), r.end(),
                            [](const auto &v) { return v.has_value(); });
      }))
    return false;
  return !check_movable();
}

bool Board::is_effective_move(InputKind input) const {
  for (int i = 0; i < 4; i++) {
    std::vector<BoardEntry> line;
    switch (input) {
    case InputKind::UP:
      line = column_at(i);
      break;
    case InputKind::DOWN:
      line = column_at(i);
      std::reverse(line.begin(), line.end());
      break;
    case InputKind::LEFT:
      line = row_at(i);
      break;
    case InputKind::RIGHT:
      line = row_at(i);
      std::reverse(line.begin(), line.end());
      break;
    }
    if (is_reducible(line))
      return true;
  }
  return false;
}

std::vector<std::pair<Block, std::pair<int, int>>>
Board::move_board(InputKind input) {
  int direction = 1;
  std::vector<std::pair<Block, std::pair<int, int>>> created_blocks;
  if (input == InputKind::DOWN || input == InputKind::RIGHT)
    direction = -1;
  for (int i = 0; i < 4; i++) {
    std::vector<BoardEntry> line;
    if (input == InputKind::UP || input == InputKind::DOWN)
      line = column_at(i);
    else
      line = row_at(i);
    if (input == InputKind::DOWN || input == InputKind::RIGHT)
      std::reverse(line.begin(), line.end());
    auto [reduced, created_blocks_line] = reduce_line(line);
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
    int empty_start = 0;
    if (input == InputKind::UP || input == InputKind::DOWN) {
      BoardMatrix::iterator it;
      if (input == InputKind::UP)
        it = board_matrix.begin();
      else
        it = board_matrix.begin() + 3;
      std::for_each(reduced.begin(), reduced.end(),
                    [&it, i, direction, &empty_start](const auto &v) {
                      (*it)[i] = v;
                      it += direction;
                      empty_start++;
                    });
      for (int j = empty_start; j < 4; j++) {
        (*it)[i] = {};
        it += direction;
      }
    } else {
      BoardRow::iterator it;
      if (input == InputKind::LEFT)
        it = board_matrix[i].begin();
      else
        it = board_matrix[i].begin() + 3;
      std::for_each(reduced.begin(), reduced.end(),
                    [&it, i, direction, &empty_start](const auto &v) {
                      *it = v;
                      it += direction;
                      empty_start++;
                    });
      for (int j = empty_start; j < 4; j++) {
        *it = {};
        it += direction;
      }
    }
  }
  std::sort(
      created_blocks.begin(), created_blocks.end(),
      [](const auto &v1, const auto &v2) { return v1.second < v2.second; });
  return created_blocks;
}
