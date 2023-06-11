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
  std::uniform_int_distribution<> first_dist(0, 15);
  int first_idx = first_dist(rng);
  std::uniform_int_distribution<> second_dist(0, 14);
  int second_idx = second_dist(rng);
  if (second_idx >= first_idx) {
    second_idx++;
    std::swap(first_idx, second_idx);
  }

  int first_y = first_idx / 4, first_x = first_idx % 4,
      second_y = second_idx / 4, second_x = second_idx % 4;
  board[{first_y, first_x}] = 1;
  board[{second_y, second_x}] = 1;
  this->output_stream << LogEntry(LogEntryKind::INITIAL,
                                  {first_y + 1, first_x + 1, second_y + 1,
                                   second_x + 1})
                      << std::endl;
}

void Game::add_block() {
  auto vacancies = board.vacant_pos();
  if (vacancies.empty())
    return;
  std::uniform_int_distribution<> pos_dist(0, vacancies.size() - 1);
  auto pos = vacancies[pos_dist(rng)];
  std::uniform_int_distribution<> power_dist(1, 5);
  int new_block_power = power_dist(rng) == 1 ? 2 : 1;
  board[pos] = new_block_power;
  output_stream << LogEntry(
                       LogEntryKind::GENERATE,
                       {pos.first + 1, pos.second + 1, 1 << new_block_power})
                << std::endl;
}

bool Game::is_win() const {
  auto &&mat = board.get_board_matrix();
  return std::any_of(mat.begin(), mat.end(), [](const auto &r) {
    return std::any_of(r.begin(), r.end(),
                       [](const auto &v) { return v == 11; });
  });
}

bool Game::is_lost() const { return board.is_finished(); }

bool Game::is_undo_buffer_empty() const {
  return !last_board_matrix.has_value();
}

OpResult Game::move_board(InputKind input) {
  if (board.is_finished())
    return OpResult::GAME_OVER;
  output_stream << LogEntry(
                       static_cast<LogEntryKind>(static_cast<int>(input) + 1),
                       {})
                << std::endl;
  if (!board.is_effective_move(input))
    return OpResult::INEFFECTIVE_MOVE;
  last_board_matrix = board.get_board_matrix();
  auto created = board.move_board(input);
  last_score = score;
  score += std::transform_reduce(
      created.cbegin(), created.cend(), 0, std::plus{},
      [](const auto &v) { return 1 << v.first.get_power(); });
  for (const auto &v : created) {
    auto [y, x] = v.second;
    output_stream << LogEntry(LogEntryKind::MERGE,
                              {x + 1, y + 1, 1 << v.first.get_power()})
                  << std::endl;
  }
  output_stream << LogEntry(LogEntryKind::SCORE, {score}) << std::endl;
  return OpResult::OK;
}

void Game::undo() {
  if (!last_board_matrix.has_value())
    return;
  if (undo_left <= 0)
    return;
  board = Board(last_board_matrix.value());
  last_board_matrix.reset();
  score = last_score.value();
  last_score.reset();
  undo_left--;
  output_stream << LogEntry(LogEntryKind::RESTORE, {undo_left}) << std::endl;
  return;
}

int Game::get_score() const { return score; }

int Game::get_undo_left() const { return undo_left; }

BoardEntry Game::get_entry(int y, int x) const { return board[{y, x}]; }
