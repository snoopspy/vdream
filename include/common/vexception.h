// ----------------------------------------------------------------------------
//
// VDream Component Suite version 9.0.1
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __V_EXCEPTION_H__
#define __V_EXCEPTION_H__

#include <exception>
#include <QString>

// ----- gilgil temp 2014.12.31 -----
/*
class VException : public std::exception
{
public:
  VException(int code, QString msg, bool log = true);
  VException(int errno);

public:
  int     code;
  QString msg;
  virtual const char* what() const throw();

public:
  static bool initialize();
  static bool finalize();
};
*/
// ----------------------------------

#endif // __V_EXCEPTION_H__
