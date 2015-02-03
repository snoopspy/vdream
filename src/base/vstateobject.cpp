#include <VStateObject>

VStateObject::VStateObject(void* owner) : VObject(owner)
{
  m_state = VState::Closed;
  tag = 0;
  error.clear();
}

VStateObject::~VStateObject()
{
  if (m_state != VState::Closed)
  {
    LOG_FATAL("%s close must be called in descendant of VStateObject(state=%d) %p", qPrintable(objectName()), (int)m_state, this);
  }
}

bool VStateObject::open()
{
  if (m_state != VState::Closed)
  {
    SET_ERROR(VError, QString("not closed state(%1) %2 %3").arg((int)m_state).arg(className()).arg(objectName()), VError::NOT_CLOSED_STATE);
    return false;
  }

  if (objectName() == "") setObjectName(className());
  m_state = VState::Opening;
  tag     = 0;
  error.clear();

  bool res = doOpen();

  if (!res)
  {
    doClose();
    m_state = VState::Closed;
    return false;
  }

  m_state = VState::Opened;
  emit opened();
  return true;
}

bool VStateObject::close()
{
  if (m_state != VState::Opened)
  {
    return false; // no action
  }

  m_state = VState::Closing;

  bool res = doClose();

  if (!res)
  {
    // m_state = VState::Closed; // do not change state if doClose() return false;
    return false;
  }

  m_state = VState::Closed;
  emit closed();
  return true;
}

bool VStateObject::close(bool wait, VTimeout timeout)
{
  bool res = close();
  if (res && wait)
    res = this->wait(timeout);
  return res;
}

bool VStateObject::wait(VTimeout timeout)
{
  Q_UNUSED(timeout);
  return true;
}

bool VStateObject::doOpen()
{
  SET_ERROR(VError, QString("virtual function call %1 %2").arg(className()).arg(objectName()), VError::VIRTUAL_FUNCTION_CALL);
  LOG_FATAL("virtual function call error %s %s", qPrintable(className()), qPrintable(objectName()));
  return false;
}

bool VStateObject::doClose()
{
  SET_ERROR(VError, QString("virtual function call %1 %2").arg(className()).arg(objectName()), VError::VIRTUAL_FUNCTION_CALL);
  LOG_FATAL("virtual function call error %s %s", qPrintable(className()), qPrintable(objectName()));
  return false;
}
