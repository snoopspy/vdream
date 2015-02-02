// ----------------------------------------------------------------------------
//
// VDream Component Suite version 9.0.1
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __V_BASE_H__
#define __V_BASE_H__

// #define WIN32_LEAN_AND_MEAN // gilgil temp 2015.01.21
#include <QtCore>
#include <VSystem>
#ifdef WIN32
#include <VWindows>
#endif // WIN32
#ifdef linux
#include <VLinux>
#endif // linux

// ----------------------------------------------------------------------------
// Define
// ----------------------------------------------------------------------------
#ifndef SAFE_DELETE
#define SAFE_DELETE(A) { if(A != NULL) { delete A; A = NULL; } }
#endif // SAFE_DELETE

#ifndef SAFE_FREE
#define SAFE_FREE(A)   { if(A != NULL) { free(A); A = NULL; } }
#endif // SAFE_FREE

// ----------------------------------------------------------------------------
// VBase
// ----------------------------------------------------------------------------
class VBase
{
public:
	static const char* VDREAM_VERSION;
	static const char* getClassName(const char* value);

	static const int      BUF_SIZE = 65536; // bytes
	static const VTimeout TIMEOUT  = 10000; // 10 sec
	static const int      PORT     = 10065;
};

// ----- gilgil temp 2015.02.03 -----
/*
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
  VState()                    {                      } // default ctor
  VState(const _VState value) { this->value = value; } // conversion ctor
  operator _VState() const    { return value;        } // cast operator

public:
  VState(const QString s);
  QString str() const;
};
*/
// ----------------------------------

#endif // __V_BASE_H__
