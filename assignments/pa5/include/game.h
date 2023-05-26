#pragma once

#include "board.h"

#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <random>
#include <utility>

enum class OpResult {
  OK,
  GAME_OVER,
  UNDO_BUF_EMPTY,
  UNDO_COUNT_ZERO,
  INEFFECTIVE_MOVE
};

class Game {
private:
  Board board;
  int score = 0;
  int undo_left = 3;
  std::optional<BoardMatrix> last_board_matrix = {};

  std::mt19937 rng;

  std::unique_ptr<std::ostream> output_stream;

public:
  Game();
  Game(uint32_t seed, std::unique_ptr<std::ostream> output_stream);

  void add_block();
  OpResult move_board(InputKind input);
  OpResult undo();

  bool is_win() const;
  bool is_lost() const;
  int get_score() const;
  int get_undo_left() const;
  BoardEntry get_entry(int y, int x) const;
};
