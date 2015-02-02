// ----------------------------------------------------------------------------
//
// VDream Component Suite version 9.1
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __V_STATE_H__
#define __V_STATE_H__

#include <QMetaType>
#include <QString>

// ----------------------------------------------------------------------------
// VState
// ----------------------------------------------------------------------------
class VState
{
public:
  enum _VState
  {
    None,    // 0
    Closed,  // 1
    Opening, // 2
    Opened,  // 3
    Closing  // 4
  };

protected:
  _VState value;

public:
  VState() {}

  VState(const _VState value) { this->value = value; }
  operator _VState() const { return value; }

  VState(const QString s);
  operator QString() const;
};
Q_DECLARE_METATYPE(VState)

#endif // __V_STATE_H__
