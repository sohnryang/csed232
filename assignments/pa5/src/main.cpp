#include "ui/gameui.h"

#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv); // create application
  GameUi *g = new GameUi();   // create game widget
  QMainWindow w;              // create a main window
  w.setCentralWidget(g);      // set game widget as the central widget
  w.resize(1300, 1000);       // set the size of the window
  w.show();                   // show the window
  return a.exec();            // run the event loop
}
