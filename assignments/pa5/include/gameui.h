#pragma once

#include "game.h"

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
  QHBoxLayout *root;
  QGridLayout *board_grid;
  QVBoxLayout *sidebar;
  QPushButton *restore_button;
  QPushButton *exit_button;
  QLabel *score_label;
  Game current_game;
  std::ofstream log_stream;

  void update_ui();

private slots:
  void exit_button_click();
  void restore_button_click();

public:
  GameUi();
  ~GameUi();

  void keyPressEvent(QKeyEvent *event) override;
};
