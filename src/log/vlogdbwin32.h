// ----------------------------------------------------------------------------
//
// VDream Component Suite version 9.0
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __V_LOG_DBWIN32_H__
#define __V_LOG_DBWIN32_H__

#ifdef _WIN32

#include <VLog>

// ----------------------------------------------------------------------------
// VLogDBWin32
// ----------------------------------------------------------------------------
class VLogDBWin32 : public VLog
{
  Q_OBJECT

public:
  Q_INVOKABLE VLogDBWin32(void* owner = NULL) : VLog(owner) {}
  virtual ~VLogDBWin32() {}

protected:
  virtual void write(const char* buf, int len);

public:
  virtual VLog* createByURI(const QString& uri);
};

#endif // _WIN32

#endif // __V_LOG_DBWIN32_H__
