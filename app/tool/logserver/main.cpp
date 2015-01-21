#include <QApplication>
#include "mainwindow.h"
#include <VApp>

int run(QApplication& a)
{
  MainWindow w;
  w.show();
  return a.exec();
}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  VApp::initialize(true, true, "");
  int res = run(a);
  VApp::finalize();
  return res;
}
