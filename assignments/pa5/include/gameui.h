#pragma once

#include "game.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

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

  void update_ui();

public:
  GameUi();
  ~GameUi();

  void keyPressEvent(QKeyEvent *event) override;
};
