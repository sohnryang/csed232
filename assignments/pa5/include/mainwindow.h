#pragma once

#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow {
  Q_OBJECT

private:
  QPushButton *button;

private slots:
  void handle_button();

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
};
