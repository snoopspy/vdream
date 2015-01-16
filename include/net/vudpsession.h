// ----------------------------------------------------------------------------
//
// VDream Component Suite version 9.0
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __V_UDP_SESSION_H__
#define __V_UDP_SESSION_H__

#include <VNetSession>

// ----------------------------------------------------------------------------
// VUdpSession
// ----------------------------------------------------------------------------
class VUdpSession : public VNetSession, protected VStateLockable
{
public:
  VUdpSession(void* owner = NULL);
  virtual ~VUdpSession();

protected:
  virtual bool doOpen();
  virtual bool doClose();
  virtual int  doRead(char* buf, int size);
  virtual int  doWrite(char* buf, int size);

private:
  static void logAddr(struct sockaddr_in* sockAddr);
public:
  /// socket handle. read only(set in other class)
  SOCKET handle;
  /// sockaddr_in structure. read only(set in other class)
  struct sockaddr_in addr;

public:
  Ip  getLocalIP();
  Ip  getRemoteIP();
  int getLocalPort();
  int getRemotePort();

public:
  bool operator == (const VUdpSession& rhs) const;
};

#endif // __V_UDP_SESSION_H__
