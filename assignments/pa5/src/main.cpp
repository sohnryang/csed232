#include "ui/gameui.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  GameUi g;
  g.show();
  return a.exec();
}
