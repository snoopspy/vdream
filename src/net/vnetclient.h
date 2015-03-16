// ----------------------------------------------------------------------------
//
// VDream Component Suite version 9.0
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __V_NET_CLIENT_H__
#define __V_NET_CLIENT_H__

#include <VNet>
#include <VObjectWidget>

// ----------------------------------------------------------------------------
// VNetClient
// ----------------------------------------------------------------------------
class VNetClient : public VNet, public VOptionable
{
  Q_OBJECT
  Q_PROPERTY(QString host MEMBER host)
  Q_PROPERTY(int port MEMBER port)
  Q_PROPERTY(QString localHost MEMBER localHost)
  Q_PROPERTY(int localPort MEMBER localPort)

public:
  VNetClient(void* owner = NULL);
  virtual ~VNetClient();

public:
  int onceWriteSize;
public:
  /// IP address or HostName
  QString host;
  /// Port No
  int port;
  /// Local IP address or HostName
  QString localHost;
  /// Local Port No
  int localPort;

public:
  virtual void load(VXml &xml);
  virtual void save(VXml &xml);

#ifdef QT_GUI_LIB
public: // for VOptionable
  virtual void optionAddWidget(QLayout* layout);
  virtual void optionSaveDlg(QDialog* dialog);
#endif // QT_GUI_LIB
};

#endif // __V_NET_CLIENT_H__
