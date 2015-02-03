// ----------------------------------------------------------------------------
//
// VDream Component Suite version 9.0
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __V_OBJECT_H__
#define __V_OBJECT_H__

#include <QObject>

#include <VBase>
#include <VError>
#include <VState>
#include <VXml>

// ----------------------------------------------------------------------------
// VObjectConnection
// ----------------------------------------------------------------------------
class VObjectConnection
{
public:
  VObjectConnection(QByteArray  signal, QObject* receiver, QByteArray  slot);
  VObjectConnection(const char* signal, QObject* receiver, const char* slot);

public:
  QByteArray signal;
  QObject*   receiver;
  QByteArray slot;

public:
  bool operator == (const VObjectConnection& r) const;
};

// ----------------------------------------------------------------------------
// VObjectConnections
// ----------------------------------------------------------------------------
class VObjectConnections : public QList<VObjectConnection>
{
};

// ----------------------------------------------------------------------------
// VObject
// ----------------------------------------------------------------------------
class VObject :
  public QObject,
  public VXmlable
{
  Q_OBJECT

public:
  void* owner;

public:
  VObject(void* owner = NULL);
  virtual ~VObject();

public:
  VObjectConnections connections;
  static bool connect(QObject* sender, const char* signal, QObject* receiver, const char* slot, Qt::ConnectionType type = Qt::AutoConnection);
  static bool connect(QObject *sender, const QMetaMethod &signal, QObject *receiver, const QMetaMethod &slot, Qt::ConnectionType type = Qt::AutoConnection);
  static bool disconnect(QObject* sender, const char* signal, QObject* receiver, const char* slot);
  static bool disconnect(QObject *sender, const QMetaMethod &signal, QObject *receiver, const QMetaMethod &slot);
  static QMetaMethod findMethod(QObject* object, QString methodName);

public:
  QString className() { return this->metaObject()->className(); }

public:
  virtual void load(VXml xml);
  virtual void save(VXml xml);
};

#endif // __V_OBJECT_H__
