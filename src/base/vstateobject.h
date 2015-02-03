// ----------------------------------------------------------------------------
//
// VDream Component Suite version 9.01
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __V_STATE_OBJECT_H__
#define __V_STATE_OBJECT_H__

#include <VLog>
#include <VObject>
#include <VState>

// ----------------------------------------------------------------------------
// VStateObject
// ----------------------------------------------------------------------------
class VStateObject : public VObject
{
  Q_OBJECT
  Q_PROPERTY(VState::VState state READ state)
  Q_PROPERTY(bool active READ active)

public:
  VStateObject(void* owner = NULL);
  virtual ~VStateObject();

protected:
  VState m_state;

public:
  VState state() { return m_state; }
  bool active() { return m_state == VState::Opened; }

public slots:
  virtual bool open();
  virtual bool close();

public:
  virtual bool close(bool wait, VTimeout timeout = VBase::TIMEOUT);
  virtual bool wait(VTimeout timeout = VBase::TIMEOUT);

protected:
  virtual bool doOpen();
  virtual bool doClose();

signals:
  void opened();
  void closed();
};

#endif // __V_STATE_OBJECT_H__
