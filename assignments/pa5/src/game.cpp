#include "game.h"
#include "block.h"
#include "board.h"

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <functional>
#include <memory>
#include <numeric>
#include <ostream>
#include <random>
#include <utility>

Game::Game()
    : Game(std::random_device()(),
           std::make_unique<std::ofstream>("progress.txt")) {}

Game::Game(uint32_t seed, std::unique_ptr<std::ostream> output_stream)
    : rng(seed), output_stream(std::move(output_stream)) {
  std::uniform_int_distribution<> first_dist(0, 15);
  int first_idx = first_dist(rng);
  std::uniform_int_distribution<> second_dist(0, 14);
  int second_idx = second_dist(rng);
  if (second_idx >= first_idx)
    second_idx++;
  board[{first_idx / 4, first_idx % 4}] = 1;
  board[{second_idx / 4, second_idx % 4}] = 1;
}

void Game::add_block() {
  auto vacancies = board.vacant_pos();
  if (vacancies.empty())
    return;
  std::uniform_int_distribution<> pos_dist(0, vacancies.size() - 1);
  auto pos = vacancies[pos_dist(rng)];
  std::uniform_int_distribution<> power_dist(1, 5);
  board[pos] = power_dist(rng) == 1 ? 2 : 1;
}

bool Game::is_win() const {
  auto &&mat = board.get_board_matrix();
  return std::any_of(mat.begin(), mat.end(), [](const auto &r) {
    return std::any_of(r.begin(), r.end(),
                       [](const auto &v) { return v == 11; });
  });
}

bool Game::is_lost() const { return board.is_finished(); }

OpResult Game::move_board(InputKind input) {
  if (board.is_finished())
    return OpResult::GAME_OVER;
  if (!board.is_effective_move(input))
    return OpResult::INEFFECTIVE_MOVE;
  last_board_matrix = board.get_board_matrix();
  auto created = board.move_board(input);
  score += std::transform_reduce(
      created.cbegin(), created.cend(), 0, std::plus{},
      [](const auto &v) { return 1 << v.first.get_power(); });
  return OpResult::OK;
}

OpResult Game::undo() {
  if (!last_board_matrix.has_value())
    return OpResult::UNDO_BUF_EMPTY;
  if (undo_left <= 0)
    return OpResult::UNDO_COUNT_ZERO;
  board = Board(last_board_matrix.value());
  undo_left--;
  return OpResult::OK;
}

int Game::get_score() const { return score; }

int Game::get_undo_left() const { return undo_left; }

BoardEntry Game::get_entry(int y, int x) const { return board[{y, x}]; }
