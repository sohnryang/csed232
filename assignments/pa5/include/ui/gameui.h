#pragma once

#include "src/game.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include <fstream>
#include <memory>

class GameUi : public QWidget {
  Q_OBJECT

private:
  // Root hbox layout.
  QHBoxLayout *root;

  // Grid layout for board.
  QGridLayout *board_grid;

  // Vertical layout for sidebar.
  QVBoxLayout *sidebar;

  // Restore button.
  QPushButton *restore_button;

  // Exit button.
  QPushButton *exit_button;

  // Label for score.
  QLabel *score_label;

  // Game object for current game's status.
  Game current_game;

  // Stream for log output.
  std::ofstream log_stream;

  // Update UI according to game state.
  void update_ui();

private slots:
  // Event handler for exit button.
  void exit_button_click();

  // Event handler for restore button.
  void restore_button_click();

public:
  // Default constructor.
  GameUi();

  // Key press event handler.
  void keyPressEvent(QKeyEvent *event) override;
};
