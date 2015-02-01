#include <VTcpClient>
#include <VDebugNew>

REGISTER_METACLASS(VTcpClient, VNet)

// ----------------------------------------------------------------------------
// VTcpClient
// ----------------------------------------------------------------------------
VTcpClient::VTcpClient(void* owner) : VNetClient(owner)
{
  tcpSession = new VTcpSession(this);
}

VTcpClient::~VTcpClient()
{
  close();
  SAFE_DELETE(tcpSession);
}

bool VTcpClient::close()
{
  //
  // Hang might be occurred when calling open in one thread and calling close in other thread.
  // So call tcpSession->doClose forcibly preventing hang.
  //
  tcpSession->doClose();
  return VNetClient::close();
}

bool VTcpClient::doOpen()
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
  tcpSession->handle = socket(AF_INET, SOCK_STREAM, 0);
  if (tcpSession->handle == INVALID_SOCKET)
  {
    SET_ERROR(VSocketError, "error in socket", (int)WSAGetLastError());
    return false;
  }

  // ------------------------------------------------------------------------
  // bind
  // ------------------------------------------------------------------------
  tcpSession->addr.sin_family = AF_INET;
  tcpSession->addr.sin_port = htons(quint16(localPort));
  if (localHost == 0)
  {
    tcpSession->addr.sin_addr.s_addr = INADDR_ANY;
  } else
  {
    Ip ip = VNet::resolve(localHost);
    if (ip == 0)
    {
      SET_ERROR(VNetError, QString("can not resolve host(%1)").arg(localHost), VNetError::CAN_NOT_RESOLVE_HOST);
      return false;
    }
    tcpSession->addr.sin_addr.s_addr = htonl(ip);
  }
  memset(&tcpSession->addr.sin_zero, 0, sizeof(tcpSession->addr.sin_zero));

  int res = bind(tcpSession->handle, (struct sockaddr*)&tcpSession->addr, sizeof(tcpSession->addr));
  if (res == SOCKET_ERROR)
  {
    SET_ERROR(VSocketError, QString("error in bind(%1:%2)").arg(localHost).arg(localPort), (int)WSAGetLastError());
    return false;
  }

  // ------------------------------------------------------------------------
  // connect
  // ------------------------------------------------------------------------
  tcpSession->addr.sin_family = AF_INET;
  tcpSession->addr.sin_port = htons(quint16(port));
  if (host == "")
  {
    SET_ERROR(VNetError, "host is invalid", VNetError::INVALID_HOST);
    return false;
  }
  Ip ip = VNet::resolve(host);
  if (ip == 0)
  {
    SET_ERROR(VNetError, QString("can not resolve host(%1)").arg(host), VNetError::CAN_NOT_RESOLVE_HOST);
    return false;
  }
  tcpSession->addr.sin_addr.s_addr = htonl(ip);
  memset(tcpSession->addr.sin_zero, 0, sizeof(tcpSession->addr.sin_zero));
  res = ::connect(tcpSession->handle, (struct sockaddr*)&tcpSession->addr, sizeof(tcpSession->addr));
  if (res == SOCKET_ERROR)
  {
    int lastError = (int)WSAGetLastError();
    SET_ERROR(VSocketError, QString("error in connect(%1:%2)").arg(host).arg(port), lastError);
    return false;
  }

  // ------------------------------------------------------------------------
  // ok
  // ------------------------------------------------------------------------
  tcpSession->onceWriteSize = this->onceWriteSize;
  if (!tcpSession->open()) return false;

  return true;
}

bool VTcpClient::doClose()
{
  VLock lock(stateCloseCs); // gilgil temp 2014.03.14

  tcpSession->close();
  return true;
}

int  VTcpClient::doRead(char* buf, int size)
{
  // VLock lock(stateReadCs); // gilgil temp 2014.03.14

  int res = tcpSession->read(buf, size);
  if (res == VError::FAIL)
    error = tcpSession->error;
  return res;
}

int  VTcpClient::doWrite(char* buf, int size)
{
  // VLock lock(stateWriteCs); // gilgil temp 2014.03.14

  int res = tcpSession->write(buf, size);
  if (res == VError::FAIL)
    error = tcpSession->error;
  return res;
}

void VTcpClient::load(VXml xml)
{
  VNetClient::load(xml);
}

void VTcpClient::save(VXml xml)
{
  VNetClient::save(xml);
}

#ifdef QT_GUI_LIB
void VTcpClient::optionAddWidget(QLayout* layout)
{
  VNetClient::optionAddWidget(layout);
}

void VTcpClient::optionSaveDlg(QDialog* dialog)
{
  VNetClient::optionSaveDlg(dialog);
}
#endif // QT_GUI_LIB
