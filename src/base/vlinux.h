// ----------------------------------------------------------------------------
//
// VDream Component Suite version 9.1
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __V_LINUX_H__
#define __V_LINUX_H__

#ifdef __linux__

// ----------------------------------------------------------------------------
// SOCKET
// ----------------------------------------------------------------------------
typedef int SOCKET;
#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR            (-1)

// ----------------------------------------------------------------------------
// GetLastError
// ----------------------------------------------------------------------------
#include <errno.h>
inline int GetLastError()    { return errno; }
inline int WSAGetLastError() { return errno; }

#endif // __linux__

#endif // __V_LINUX_H__
