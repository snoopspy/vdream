// ----------------------------------------------------------------------------
//
// VDream Component Suite version 9.0
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __V_LINUX_H__
#define __V_LINUX_H__

#ifdef linux
// ----------------------------------------------------------------------------
// Calling Conventions
// ----------------------------------------------------------------------------
// ----- gilgil temp 2015.01.16 -----
/*
#define __cdecl               __attribute__((__cdecl__))
#define __stdcall             __attribute__((__stdcall__))
// #define __declspec(dllexport) // gilgil temp 2012.08.11
*/
// ----------------------------------

// ----------------------------------------------------------------------------
// GetLastError()
// ----------------------------------------------------------------------------
#include <errno.h>
inline int GetLastError()    { return errno; }
inline int WSAGetLastError() { return errno; }
// inline int closesocket(int handle) { return close(handle); } // gilgil temp 2015.01.16

// ----- gilgil temp 2015.01.16 -----
/*
// ----------------------------------------------------------------------------
// Other types
// ----------------------------------------------------------------------------
typedef int  BOOL;
typedef void (*HMODULE);

typedef signed char        INT8,   *PINT8;
typedef signed short       int16_t,  *PINT16;
typedef signed int         int32_t,  *PINT32;
typedef signed long long   INT64,  *PINT64;

typedef unsigned char      uint8_t,  *PUINT8;
typedef unsigned short     uint16_t, *PUINT16;
typedef unsigned int       uint32_t, *PUINT32;
typedef unsigned long long UINT64, *PUINT64;

typedef unsigned long      ULONG_PTR, *PULONG_PTR;
typedef ULONG_PTR          DWORD_PTR, *PDWORD_PTR;
typedef unsigned char      uint8_t,   *PBYTE;
typedef unsigned short     WORD,   *PWORD;
typedef unsigned int       DWORD,  *PDWORD;
*/
// ----------------------------------

// ----- gilgil temp 2015.01.16 -----
/*
// ----------------------------------------------------------------------------
// Macro
// ----------------------------------------------------------------------------
#define MAKEWORD(a, b)      ((WORD)(((uint8_t)(((DWORD_PTR)(a)) & 0xff)) | ((WORD)((uint8_t)(((DWORD_PTR)(b)) & 0xff))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)(((DWORD_PTR)(a)) & 0xffff)) | ((DWORD)((WORD)(((DWORD_PTR)(b)) & 0xffff))) << 16))
#define LOWORD(l)           ((WORD)(((DWORD_PTR)(l)) & 0xffff))
#define HIWORD(l)           ((WORD)((((DWORD_PTR)(l)) >> 16) & 0xffff))
#define LOBYTE(w)           ((uint8_t)(((DWORD_PTR)(w)) & 0xff))
#define HIBYTE(w)           ((uint8_t)((((DWORD_PTR)(w)) >> 8) & 0xff))
*/
// ----------------------------------

// ----------------------------------------------------------------------------
// WinSock
// ----------------------------------------------------------------------------
// #include <netinet/in.h>

typedef int SOCKET;
#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR            (-1)

// typedef struct sockaddr    SOCKADDR; // gilgil temp 2015.01.16
// typedef struct in_addr     IN_ADDR; // gilgil temp 2015.01.16
// typedef struct sockaddr_in SOCKADDR_IN; // gilgil temp 2015.01.16

#endif // linux

#endif // __V_LINUX_H__
