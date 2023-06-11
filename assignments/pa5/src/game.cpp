#include "src/game.h"
#include "src/block.h"
#include "src/board.h"
#include "src/logging.h"

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <functional>
#include <ios>
#include <memory>
#include <numeric>
#include <ostream>
#include <random>
#include <utility>

Game::Game(uint32_t seed) : rng(seed), output_stream("progress.txt") {
  // Randomly add two 2-blocks.
  std::uniform_int_distribution<> first_dist(0, 15);
  int first_idx = first_dist(rng);
  std::uniform_int_distribution<> second_dist(0, 14);
  int second_idx = second_dist(rng);

  // Avoid placing two blocks in same position.
  if (second_idx >= first_idx) {
    second_idx++;
    std::swap(first_idx, second_idx);
  }

  // Calculate coordinates.
  int first_y = first_idx / 4, first_x = first_idx % 4,
      second_y = second_idx / 4, second_x = second_idx % 4;
  // Actually place the blocks to the board.
  board[{first_y, first_x}] = 1;
  board[{second_y, second_x}] = 1;

  // Log the block placements.
  this->output_stream << LogEntry(LogEntryKind::INITIAL,
                                  {first_y + 1, first_x + 1, second_y + 1,
                                   second_x + 1})
                      << std::endl;
}

std::optional<std::pair<int, int>> Game::add_block(bool two_only,
                                                   bool write_log) {
  // Get vacant positions.
  auto vacancies = board.vacant_pos();
  if (vacancies.empty())
    return {}; // stop if there is nowhere to add blocks.

  // Pick a random position.
  std::uniform_int_distribution<> pos_dist(0, vacancies.size() - 1);
  auto pos = vacancies[pos_dist(rng)];
  // Determine the number.
  int new_block_power;
  if (two_only)
    new_block_power = 1;
  else {
    std::uniform_int_distribution<> power_dist(1, 5);
    new_block_power = power_dist(rng) == 1 ? 2 : 1;
  }
  // Place the block.
  board[pos] = new_block_power;

  // Log the block placement.
  if (write_log)
    output_stream << LogEntry(
                         LogEntryKind::GENERATE,
                         {pos.first + 1, pos.second + 1, 1 << new_block_power})
                  << std::endl;
  return pos;
}

bool Game::is_win() const {
  // Get reference of the board matrix.
  const auto &mat = board.get_board_matrix();
  return std::any_of(mat.begin(), mat.end(), [](const auto &r) {
    return std::any_of(r.begin(), r.end(),
                       [](const auto &v) { return v == 11; });
  });
}

bool Game::is_lost() const { return board.is_finished(); }

bool Game::is_undo_buffer_empty() const {
  return !last_board_matrix.has_value();
}

MoveResult Game::move_board(InputKind input) {
  if (board.is_finished()) // check game over
    return MoveResult::GAME_OVER;
  // Log the input.
  output_stream << LogEntry(
                       static_cast<LogEntryKind>(static_cast<int>(input) + 1),
                       {})
                << std::endl;
  if (!board.is_effective_move(input)) // check if the move is effective
    return MoveResult::INEFFECTIVE_MOVE;

  // Save the last state to undo buffer.
  last_board_matrix = board.get_board_matrix();
  last_score = score;

  // Calculate the score of this move.
  auto created = board.move_board(input);
  score += std::transform_reduce(
      created.cbegin(), created.cend(), 0, std::plus{},
      [](const auto &v) { return 1 << v.first.get_power(); });
  // Log created blocks.
  for (const auto &v : created) {
    auto [y, x] = v.second;
    output_stream << LogEntry(LogEntryKind::MERGE,
                              {x + 1, y + 1, 1 << v.first.get_power()})
                  << std::endl;
  }
  // Log score.
  output_stream << LogEntry(LogEntryKind::SCORE, {score}) << std::endl;
  return MoveResult::OK;
}

void Game::undo() {
  // Check if undo buffer is empty.
  if (!last_board_matrix.has_value())
    return;
  // Check if we have undo count left.
  if (undo_left <= 0)
    return;
  board = Board(last_board_matrix.value()); // restore the board
  last_board_matrix.reset();                // clear the saved board
  score = last_score.value();               // restore the score
  last_score.reset();                       // clear the saved score
  undo_left--;                              // decrement the undo count

  // Log undo.
  output_stream << LogEntry(LogEntryKind::RESTORE, {undo_left}) << std::endl;
}

int Game::get_score() const { return score; }

int Game::get_undo_left() const { return undo_left; }

BoardEntry Game::get_entry(int y, int x) const { return board[{y, x}]; }
