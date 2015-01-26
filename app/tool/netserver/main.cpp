#include "widget.h"
#include <QApplication>
#include <VApp>

int run(QApplication& a)
{
  Widget w;
  w.show();
  return a.exec();
}

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  VApp::initialize();
  int res = run(a);
  VApp::finalize();
  return res;
}
