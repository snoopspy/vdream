#include <VUdpServer>
#include <VDebugNew>

REGISTER_METACLASS(VUdpServer, VNet)

// ----------------------------------------------------------------------------
// VSockAddrList
// ----------------------------------------------------------------------------
bool operator <(const struct sockaddr_in& a, const struct sockaddr_in& b)
{
  return memcmp((void*)&a, (void*)&b, sizeof(struct sockaddr_in)) < 0;
}

VSockAddrList::iterator VSockAddrList::findBySockAddr(struct sockaddr_in sockAddr)
{
  VLock lock(m_cs);
  VSockAddrList::iterator res = this->find(sockAddr);
  return res; 
}

VSockAddrList::iterator VSockAddrList::findByInAddr(struct in_addr inAddr)
{
  VLock lock(m_cs);
  for (VSockAddrList::iterator it = begin(); it != end(); it++)
  {
    const struct sockaddr_in& sockAddr = *it;
    if (sockAddr.sin_addr.s_addr == inAddr.s_addr) return it;
  }
  return end();
}

// ----------------------------------------------------------------------------
// VUdpServer
// ----------------------------------------------------------------------------
VUdpServer::VUdpServer(void* owner) : VNetServer(owner)
{
  udpSession = new VUdpSession(this);
  port = 0;
  localHost = "";
}

VUdpServer::~VUdpServer()
{
  close();
  SAFE_DELETE(udpSession);
}

bool VUdpServer::doOpen()
{
  VLock lock(stateOpenCs); // gilgil temp 2014.03.14

  if (port == 0)
  {
    SET_ERROR(VNetError, "port is zero", VNetError::PORT_IS_ZERO);
    return false;
  }

  // ------------------------------------------------------------------------
  // socket
  // ------------------------------------------------------------------------
  udpSession->handle = ::socket(AF_INET, SOCK_DGRAM, 0);
  if (udpSession->handle == INVALID_SOCKET)
    {
    SET_ERROR(VSocketError, "error in socket", (int)WSAGetLastError());
    return false;
  }

  // ------------------------------------------------------------------------
  // bind
  // ------------------------------------------------------------------------
  udpSession->addr.sin_family = AF_INET;
  udpSession->addr.sin_port = htons(quint16(port));
  if (localHost == "")
  {
    udpSession->addr.sin_addr.s_addr = INADDR_ANY;
  } else
  {
    Ip ip = VNet::resolve(localHost);
    if (ip == 0)
    {
      SET_ERROR(VNetError, QString("can not resolve host(%1)").arg(localHost), VNetError::CAN_NOT_RESOLVE_HOST);
      return false;
    }
    udpSession->addr.sin_addr.s_addr = htonl(ip);
  }
  memset(&udpSession->addr.sin_zero, 0, sizeof(udpSession->addr.sin_zero));

  int res = ::bind(udpSession->handle, (struct sockaddr*)&udpSession->addr, sizeof(udpSession->addr));
  if (res == SOCKET_ERROR)
  {
    SET_ERROR(VSocketError, QString("error in bind(%1:%2)").arg(localHost).arg(port), (int)WSAGetLastError());
    return false;
  }

  // ------------------------------------------------------------------------
  // ok
  // ------------------------------------------------------------------------
  if (!udpSession->open()) return false;

  return true;
}

bool VUdpServer::doClose()
{
  VLock lock(stateCloseCs); // gilgil temp 2014.03.14

  sockAddrList.lock();
  sockAddrList.clear();
  sockAddrList.unlock();
  udpSession->close();
  return true;
}

int VUdpServer::doRead(char* buf, int size)
{
  VLock lock(stateReadCs); // gilgil temp 2014.03.14

  struct sockaddr_in sockAddr = udpSession->addr;
  sockAddrList.insert(sockAddr);
  return udpSession->read(buf, size);
}

int VUdpServer::doWrite(char* buf, int size)
{
  VLock lock(stateWriteCs); // gilgil temp 2014.03.14

  sockAddrList.lock();
  for (VSockAddrList::iterator it = sockAddrList.begin(); it != sockAddrList.end(); it++)
  {
    const struct sockaddr_in& sockAddr = *it;
    udpSession->addr = sockAddr;
    udpSession->write(buf, size); // do not check result
  }
  sockAddrList.unlock();
  return size;
}

void VUdpServer::load(VXml xml)
{
  VNetServer::load(xml);
}

void VUdpServer::save(VXml xml)
{
  VNetServer::save(xml);
}

#ifdef QT_GUI_LIB
void VUdpServer::optionAddWidget(QLayout* layout)
{
  VNetServer::optionAddWidget(layout);

  VOptionable::addLineEdit(layout, "lePort",      "Port",       QString::number(port));
  VOptionable::addLineEdit(layout, "leLocalHost", "Local Host", localHost);
}

void VUdpServer::optionSaveDlg(QDialog* dialog)
{
  VNetServer::optionSaveDlg(dialog);

  port      = dialog->findChild<QLineEdit*>("lePort")->text().toInt();
  localHost = dialog->findChild<QLineEdit*>("leLocalHost")->text();
}
#endif // QT_GUI_LIB
