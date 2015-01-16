// ----------------------------------------------------------------------------
//
// VDream Component Suite version 9.01
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __V_ERROR_H__
#define __V_ERROR_H__

#include <typeinfo>
#include <QString>

class VError
{
public:
  enum {
    OK = 0,
    FAIL = -1,
    UNKNOWN = 1,
    NOT_SUPPORTED,
    NOT_CLOSED_STATE,
    NOT_OPENED_STATE,
    HANDLE_IS_ZERO,
    LENGTH_IS_ZERO,
    VALUE_IS_ZERO,
    POINTER_IS_NULL,
    OBJECT_IS_NULL,
    OBJECT_IS_NOT_NULL,
    NOT_SPECIFIED,
    INVALID_INDEX,
    INVALID_HANDLE,
    TIMEOUT,
    NOT_READABLE,
    NOT_WRITABLE,
    ERROR_IN_MEMORY,
    NOT_ENOUGH_MEMORY,
    VIRTUAL_FUNCTION_CALL,
    QCONNECT_FAIL,
    RUN_PROCESS,
    LOAD_FAIL,
    CAN_NOT_FIND_OBJECT
  };

public:
  std::type_info *ti;
  QString msg;
  int code;

public:
  virtual ~VError() {}
  VError(const VError& rhs);
  VError& operator = (const VError& rhs);

public:
  VError()
  {
    ti = (std::type_info*)&typeid(*this);
    msg = "";
    code = OK;
  }

  VError(const QString msg, const int code)
  {
    ti = (std::type_info*)&typeid(*this);
    this->msg = msg;
    this->code = code;
  }

public:
  const char* className();
  void clear();
  void dump();
  void dump(const char* file, const int line, const char* func); // gilgil temp 2015.01.16
  void debug(const char* file, const int line, const char* func); // gilgil temp 2015.01.16
};

#define VERROR_CTOR(ERROR_CLASS_NAME) \
  ERROR_CLASS_NAME() : VError() \
  { \
    ti = (std::type_info*)&typeid(*this); \
  } \
  ERROR_CLASS_NAME(const QString msg, const int code) : VError(msg, code) \
  { \
    ti = (std::type_info*)&typeid(*this); \
  }

#define SET_ERROR(ERROR_CLASS_NAME, MSG, CODE) \
  { \
    ERROR_CLASS_NAME tempError; \
    tempError.msg = tempError.msg; \
    tempError.code = tempError.code; \
    error = tempError; \
    error.dump(__FILE__, __LINE__, __func__); \
  }

#define SET_DEBUG_ERROR(ERROR_CLASS_NAME, MSG, CODE) \
  { \
    ERROR_CLASS_NAME tempError; \
    tempError.msg = tempError.msg; \
    tempError.code = tempError.code; \
    error = tempError; \
    error.debug(__FILE__, __LINE__, __func__); \
  }

// ----------------------------------------------------------------------------
// Error Category
// ----------------------------------------------------------------------------
static const int  VERR_CATEGORY_COMMON      = 0;
//static const int    VERR_CATEGORY_BOOST     = 1000; // gilgil temp 2015.01.16
static const int    VERR_CATEGORY_THREAD    = 2000;
//static const int    VERR_CATEGORY_XML       = 3000; // gilgil temp 2015.01.16
//static const int    VERR_CATEGORY_BUFFER    = 4000; // gilgil temp 2015.01.16
static const int    VERR_CATEGORY_FILE      = 5000;
//static const int    VERR_CATEGORY_INTERFACE = 6000; // gilgil temp 2015.01.16
//static const int    VERR_CATEGORY_REGEX     = 7000; // gilgil temp 2015.01.16

//static const int  VERR_CATEGORY_NET         = 10000; // gilgil temp 2015.01.16
static const int   VERR_CATEGORY_SNOOP      = 11000;
static const int   VERR_CATEGORY_SSL        = 12000;
//static const int   VERR_CATEGORY_VPN_DETECT = 13000; // gilgil temp 2015.01.16

//static const int  VERR_CATEGORY_VIDEO       = 20000; // gilgil temp 2015.01.16

//static const int  VERR_CATEGORY_AUDIO       = 30000; // gilgil temp 2015.01.16

//static const int  VERR_CATEGORY_OTHER       = 40000; // gilgil temp 2015.01.16

#endif // __V_ERROR_H__
