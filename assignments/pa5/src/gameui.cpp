#include "ui/gameui.h"
#include "src/board.h"
#include "src/game.h"
#include "ui/blockui.h"

#include <QApplication>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <Qt>

#include <random>
#include <sstream>

GameUi::GameUi()
    : root(new QHBoxLayout(this)), board_grid(new QGridLayout()),
      sidebar(new QVBoxLayout()), restore_button(new QPushButton("Restore")),
      exit_button(new QPushButton("Exit")), score_label(new QLabel("Score: 0")),
      current_game(std::random_device()()) {
  resize(1300, 1000);

  root->addLayout(board_grid, 10);
  root->addLayout(sidebar, 3);

  board_grid->setSpacing(10);
  for (int y = 0; y < 4; y++)
    for (int x = 0; x < 4; x++)
      board_grid->addWidget(new BlockUi(), y, x);

  sidebar->setAlignment(Qt::AlignTop | Qt::AlignLeft);
  sidebar->addWidget(score_label);
  sidebar->addStretch();
  sidebar->addWidget(restore_button);
  sidebar->addWidget(exit_button);

  restore_button->setStyleSheet("font: 20pt;");
  restore_button->setFixedSize(300, 200);
  restore_button->setFocusPolicy(Qt::NoFocus);

  exit_button->setStyleSheet("font: 20pt;");
  exit_button->setFixedSize(300, 200);
  exit_button->setFocusPolicy(Qt::NoFocus);

  score_label->setStyleSheet("font: 50pt;");
  score_label->setAlignment(Qt::AlignCenter);

  connect(exit_button, &QPushButton::clicked, this, &GameUi::exit_button_click);
  connect(restore_button, &QPushButton::clicked, this,
          &GameUi::restore_button_click);
  update_ui();
  setFocusPolicy(Qt::StrongFocus); // ensure that the widget can get focus
}

void GameUi::update_ui() {
  for (int y = 0; y < 4; y++)
    for (int x = 0; x < 4; x++) {
      auto old_widget = board_grid->itemAtPosition(y, x)->widget();
      BlockUi *new_widget;
      auto entry = current_game.get_entry(y, x);
      if (entry.has_value())
        new_widget = new BlockUi(nullptr, entry.value());
      else
        new_widget = new BlockUi();
      board_grid->replaceWidget(old_widget, new_widget);
      delete old_widget;
    }
  std::ostringstream st;
  st << "Score: ";
  st << current_game.get_score();
  score_label->setText(st.str().c_str());
}

void GameUi::exit_button_click() { QApplication::exit(); }

void GameUi::restore_button_click() {
  if (current_game.is_undo_buffer_empty()) {
    QMessageBox message;
    message.setText("There is no previously saved board in the buffer.");
    message.setWindowTitle("Restore");
    message.exec();
    return;
  } else if (current_game.get_undo_left() <= 0) {
    QMessageBox message;
    message.setText(
        "No more chance to restore the board to its previous state.");
    message.setWindowTitle("Restore");
    message.exec();
    return;
  }
  std::ostringstream st;
  st << "Restore the game board to its previous state?" << std::endl
     << std::endl
     << "Remaining chances: " << current_game.get_undo_left();
  auto reply = QMessageBox::question(this, "Restore", st.str().c_str(),
                                     QMessageBox::Yes | QMessageBox::No);
  if (reply == QMessageBox::No)
    return;
  current_game.undo();
  update_ui();
}

void GameUi::keyPressEvent(QKeyEvent *event) {
  InputKind dir;
  if (event->key() == Qt::Key_Up || event->key() == Qt::Key_K)
    dir = InputKind::UP;
  else if (event->key() == Qt::Key_Down || event->key() == Qt::Key_J)
    dir = InputKind::DOWN;
  else if (event->key() == Qt::Key_Left || event->key() == Qt::Key_H)
    dir = InputKind::LEFT;
  else if (event->key() == Qt::Key_Right || event->key() == Qt::Key_L)
    dir = InputKind::RIGHT;
  else
    return;
  auto res = current_game.move_board(dir);
  if (res == OpResult::GAME_OVER) {
    QMessageBox message;
    std::ostringstream st;
    st << "You lose..." << std::endl
       << std::endl
       << "Score: " << current_game.get_score();
    message.setText(st.str().c_str());
    message.setWindowTitle("Lose");
    message.exec();
    return;
  }
  if (res == OpResult::INEFFECTIVE_MOVE)
    return;
  current_game.add_block();
  update_ui();
  if (current_game.is_win()) {
    int current_score = current_game.get_score();
    QTimer::singleShot(1000, this, [current_score]() {
      QMessageBox message;
      std::ostringstream st;
      st << "Congratulations!" << std::endl
         << std::endl
         << "Score: " << current_score;
      message.setText(st.str().c_str());
      message.setWindowTitle("Win");
      message.exec();
    });
  }
}
