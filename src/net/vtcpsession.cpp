#include <VTcpSession>
#include <VDebugNew>

#ifdef __linux__
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif // __linux__

// ----------------------------------------------------------------------------
// VTcpSession
// ----------------------------------------------------------------------------
VTcpSession::VTcpSession(void* owner) : VNetSession(owner)
{
  handle = INVALID_SOCKET;
  memset(&addr, 0, sizeof(addr));
}

VTcpSession::~VTcpSession()
{
  close();
}

bool VTcpSession::doOpen()
{
  VLock lock(stateOpenCs); // gilgil temp 2014.03.14

  if (handle == INVALID_SOCKET)
  {
    SET_ERROR(VError, "handle is zero", VError::HANDLE_IS_ZERO);
    return false;
  }
  return true;
}

bool VTcpSession::doClose()
{
  VLock lock(stateCloseCs); // gilgil temp 2014.03.14

  if (handle == INVALID_SOCKET) return true;

  //
  // shutdown
  //
  int res = ::shutdown(handle, SD_BOTH);
  if (res == SOCKET_ERROR)
  {
    SET_DEBUG_ERROR(VSocketError, "error in shutdown", (int)WSAGetLastError());
  }

  //
  // closesocket
  //
#ifdef _WIN32
  res = ::closesocket(handle);
#endif // _WIN32
#ifdef __linux__
  res = ::close(handle);
#endif // __linux__
  if (res == SOCKET_ERROR)
  {
    SET_ERROR(VSocketError, "error in closesocket", (int)WSAGetLastError());
  }

  handle = INVALID_SOCKET;
  return true;
}

int VTcpSession::doRead(char* buf, int size)
{
  VLock lock(stateReadCs); // gilgil temp 2014.03.14

  int res = ::recv(handle, buf, size, 0);
  if (res == SOCKET_ERROR)
  {
    SET_DEBUG_ERROR(VSocketError, "error in recv", (int)WSAGetLastError());
    return VError::FAIL;
  }
  // sometimes, read length can be 0(zero), and check if return value is not zero.
  if (res == 0)
  {
    SET_DEBUG_ERROR(VNetError, "recv return zero", VNetError::ERROR_IN_RECV);
    return VError::FAIL;
  }
  return res;
}

int VTcpSession::doWrite(char* buf, int size)
{
  VLock lock(stateWriteCs); // gilgil temp 2014.03.14

  int res;
  int restSize = size;

  while (true)
  {
    if (onceWriteSize!= 0 && restSize > onceWriteSize) restSize = onceWriteSize;
    res = ::send(handle, buf, restSize, 0);
    if (res == SOCKET_ERROR)
    {
      SET_ERROR(VSocketError, "error in send", (int)WSAGetLastError());
      return VError::FAIL;
    }
    buf += res;
    restSize -= res;
    if (restSize == 0) break;
  }
  return size;
}

Ip VTcpSession::getLocalIP()
{
  socklen_t size;
  struct sockaddr_in sockAddr;

  if (handle == INVALID_SOCKET) return 0;
  size = sizeof(sockAddr);
  if (::getsockname(handle, (struct sockaddr*)&sockAddr, &size) != 0) return 0;
  Ip res = *((Ip*)&(sockAddr.sin_addr));
  res = ntohl(res);
  return res;
}

Ip VTcpSession::getRemoteIP()
{
  socklen_t size;
  struct sockaddr_in sockAddr;

  if (handle == INVALID_SOCKET) return 0;
  size = sizeof(sockAddr);
  if (::getpeername(handle, (struct sockaddr*)&sockAddr, &size) != 0) return 0;
  Ip res = *((Ip*)&(sockAddr.sin_addr));
  res = ntohl(res);
  return res;
}

int VTcpSession::getLocalPort()
{
  socklen_t size;
  struct sockaddr_in sockAddr;

  if (handle == INVALID_SOCKET) return 0;
  size = sizeof(sockAddr);
  if (::getsockname(handle, (struct sockaddr*)&sockAddr, &size) != 0) return 0;
  int res = ntohs(sockAddr.sin_port);
  return res;
}

int VTcpSession::getRemotePort()
{
  socklen_t size;
  struct sockaddr_in sockAddr;

  if (handle == INVALID_SOCKET) return 0;
  size = sizeof(sockAddr);
  if (::getpeername(handle, (struct sockaddr*)&sockAddr, &size) != 0) return 0;
  int res = ntohs(sockAddr.sin_port);
  return res;
}

bool VTcpSession::operator == (const VTcpSession& rhs) const
{
  if (handle != rhs.handle) return false;
  if (memcmp(&addr, &rhs.addr, sizeof(addr)) != 0) return false;
  return true;
}
