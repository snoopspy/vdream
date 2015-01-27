// ----------------------------------------------------------------------------
//
// VDream Component Suite version 8.0
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __MY_LOG_H__
#define __MY_LOG_H__

#include <QObject>
#include <VThread>
// #include <VXmlDoc> // gilgil temp 2015.01.27
#include <VLogUdp>
#include <VUdpServer>

class MyLogSync : public QObject
{
  Q_OBJECT

  friend class MyLog;

signals:
  void onMessage(QString s);
};

// ----------------------------------------------------------------------------
// MyLog
// ----------------------------------------------------------------------------
class MyLog : public VObject, public VRunnable
{
public:
  MyLog();
  virtual ~MyLog();

public:
  VUdpServer* udpServer;
  MyLogSync  sync;

public: // propertied
  bool autoOpen;
  bool timeShow;

protected:
  VLog* log;

public:
  virtual bool doOpen();
  virtual bool doClose();

protected:
  virtual void run();

public:
  virtual void load(VRep& rep);
  virtual void save(VRep& rep);
};

#endif // __MY_LOG_H__
