#include "mylog.h"

// ----------------------------------------------------------------------------
// MyLog
// ----------------------------------------------------------------------------
MyLog::MyLog()
{
  udpServer       = new VUdpServer;
  udpServer->port = VLogUdp::DEFAULT_PORT;
  autoOpen        = true;
  timeShow        = true;
}

MyLog::~MyLog()
{
  close();
  SAFE_DELETE(udpServer);
}

bool MyLog::doOpen()
{
  bool res = udpServer->open();
  if (!res)
  {
    error = udpServer->error;
    return false;
  }

  res = runThread().open();
  if (!res)
  {
    error = runThread().error;
    return false;
  }

  return true;
}

bool MyLog::doClose()
{
  udpServer->close();
  runThread().close();
  return true;
}

void MyLog::run()
{
  char buf[VBase::BUF_SIZE + 1];
  while (runThread().active())
  {
    int readLen = udpServer->udpSession->read(buf, VBase::BUF_SIZE);
    if (readLen == VError::FAIL) continue;
    buf[readLen] = '\0';
    QString qs = QString::fromLocal8Bit(buf);
    emit sync.onMessage(qs);
  }
}

void MyLog::load(VRep& rep)
{
  VObject::load(xml);
  udpServer->load(rep.gotoChild("udpServer"));
  runThread().load(rep.gotoChild("thread"));
  autoOpen = rep.getBool("autoOpen", autoOpen);
  timeShow = rep.getBool("timeShow", timeShow);
}

void MyLog::save(VRep& rep)
{
  VObject::save(xml);
  udpServer->save(rep.gotoChild("udpServer"));
  runThread().save(rep.gotoChild("thread"));
  rep.setBool("autoOpen", autoOpen);
  rep.setBool("timeShow", timeShow);
}
