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
  LOG_INFO("webproxy started %s", VBase::VDREAM_VERSION);
  int res = run(a);
  VApp::finalize();
  LOG_INFO("webproxy terminated");
  return res;
}
