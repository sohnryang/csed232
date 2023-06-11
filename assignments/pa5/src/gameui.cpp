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
  resize(1300, 1000); // resize the window to the specified size

  // Add board grid layout and sidebar layout.
  root->addLayout(board_grid, 10);
  root->addLayout(sidebar, 3);

  board_grid->setSpacing(10); // set spacing for board.
  for (int y = 0; y < 4; y++)
    for (int x = 0; x < 4; x++)
      board_grid->addWidget(new BlockUi(), y, x); // add widgets

  // Add widgets to sidebar.
  sidebar->setAlignment(Qt::AlignTop | Qt::AlignLeft);
  sidebar->addWidget(score_label); // add score label
  sidebar->addStretch(); // add spacing between score label and buttons
  sidebar->addWidget(restore_button); // add restore button
  sidebar->addWidget(exit_button);    // add exit button

  // Configure the restore button.
  restore_button->setStyleSheet("font: 20pt;"); // set font size
  restore_button->setFixedSize(300, 200);       // set size of the button
  // Ensure that the button cannot steal focus.
  restore_button->setFocusPolicy(Qt::NoFocus);

  // Configure the exit button.
  exit_button->setStyleSheet("font: 20pt;"); // set font size
  exit_button->setFixedSize(300, 200);       // set size of the button
  // Ensure that the button cannot steal focus.
  exit_button->setFocusPolicy(Qt::NoFocus);

  // Configure the score label.
  score_label->setStyleSheet("font: 50pt;");  // set font size
  score_label->setAlignment(Qt::AlignCenter); // set text alignment

  // Add event handler for restore and exit button.
  connect(exit_button, &QPushButton::clicked, this, &GameUi::exit_button_click);
  connect(restore_button, &QPushButton::clicked, this,
          &GameUi::restore_button_click);
  update_ui();
  setFocusPolicy(Qt::StrongFocus); // ensure that the widget can get focus
}

void GameUi::update_ui() {
  for (int y = 0; y < 4; y++)
    for (int x = 0; x < 4; x++) {
      // Get the old widget.
      auto old_widget = board_grid->itemAtPosition(y, x)->widget();
      BlockUi *new_widget;
      auto entry = current_game.get_entry(y, x);
      if (entry.has_value())
        new_widget = new BlockUi(nullptr, entry.value());
      else
        new_widget = new BlockUi();
      // Replace the old one with newer one.
      board_grid->replaceWidget(old_widget, new_widget);
      delete old_widget; // deallocate the old widget
    }

  // Update the score label.
  std::ostringstream st;
  st << "Score: ";
  st << current_game.get_score();
  score_label->setText(st.str().c_str());
}

void GameUi::exit_button_click() { QApplication::exit(); }

void GameUi::restore_button_click() {
  if (current_game.get_undo_left() <= 0) {
    QMessageBox message; // message box to show
    message.setText(
        "No more chance to restore the board to its previous state.");
    message.setWindowTitle("Restore");
    message.exec(); // show the message box
    return;
  } else if (current_game.is_undo_buffer_empty()) {
    QMessageBox message; // message box to show
    message.setText("There is no previously saved board in the buffer.");
    message.setWindowTitle("Restore");
    message.exec(); // show the message box
    return;
  }

  // Create message text using string stream.
  std::ostringstream st;
  st << "Restore the game board to its previous state?" << std::endl
     << std::endl
     << "Remaining chances: " << current_game.get_undo_left();
  auto reply = QMessageBox::question(this, "Restore", st.str().c_str(),
                                     QMessageBox::Yes | QMessageBox::No);
  if (reply == QMessageBox::No) // abort if the user does not want to restore
    return;
  current_game.undo(); // undo the game
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
    return; // ignore other keys
  auto res = current_game.move_board(dir);
  if (res == MoveResult::GAME_OVER) {
    QMessageBox message; // message box to show
    // Create message text using string stream.
    std::ostringstream st;
    st << "You lose..." << std::endl
       << std::endl
       << "Score: " << current_game.get_score();
    message.setText(st.str().c_str());
    message.setWindowTitle("Lose");
    message.exec(); // show the message box
    return;
  }
  if (res == MoveResult::INEFFECTIVE_MOVE)
    return; // do nothing if the move is ineffective
  update_ui();
  // Check the winning condition.
  if (current_game.is_win()) {
    int current_score = current_game.get_score();
    // Use QTimer to show the message box after one second.
    QTimer::singleShot(1000, this, [current_score]() {
      QMessageBox message; // message box to show
      std::ostringstream st;
      st << "Congratulations!" << std::endl
         << std::endl
         << "Score: " << current_score;
      message.setText(st.str().c_str());
      message.setWindowTitle("Win");
      message.exec(); // show the message box
    });
  }
}
