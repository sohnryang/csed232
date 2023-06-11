#pragma once

#include "board.h"

#include <cstdint>
#include <fstream>
#include <memory>
#include <optional>
#include <random>
#include <utility>

// Move results.
enum class MoveResult { OK, GAME_OVER, INEFFECTIVE_MOVE };

class Game {
private:
  // Board of the game.
  Board board;

  // Game score.
  int score = 0;

  // Undo count left.
  int undo_left = 3;

  // Board matrix of the undo state.
  std::optional<BoardMatrix> last_board_matrix = {};

  // Score of the undo state.
  std::optional<int> last_score = {};

  // Random number generator.
  std::mt19937 rng;

  // Stream for log output.
  std::ofstream output_stream;

public:
  // Constructor with seed given.
  Game(uint32_t seed);

  // Add a block to a random position of the board.
  void add_block();

  // Move the board with given input.
  MoveResult move_board(InputKind input);

  // Undo the game.
  void undo();

  // Check the win condition.
  bool is_win() const;

  // Check the lose condition.
  bool is_lost() const;

  // Check if undo buffer is empty.
  bool is_undo_buffer_empty() const;

  // Getter for score.
  int get_score() const;

  // Getter for undo_left;
  int get_undo_left() const;

  // Getter for a block at specific position.
  BoardEntry get_entry(int y, int x) const;
};
