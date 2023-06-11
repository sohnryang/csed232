#include "ui/gameui.h"

#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  GameUi *g = new GameUi();
  QMainWindow w;
  w.setCentralWidget(g);
  w.resize(1300, 1000);
  w.show();
  return a.exec();
}
