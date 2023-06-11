#include "ui/mainwindow.h"

#include <QMessageBox>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  button = new QPushButton("Greet", this);
  button->setFixedSize(100, 50);
  connect(button, &QPushButton::released, this, &MainWindow::handle_button);
}

MainWindow::~MainWindow() {}

void MainWindow::handle_button() {
  QMessageBox mbox;
  mbox.setText("Hell world!");
  mbox.exec();
}
