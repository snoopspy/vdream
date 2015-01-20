// #define _SCL_SECURE_NO_DEPRECATE // for remive warinig 'std::_Copy_opt' was declared deprecated // gilgil temp 2014.12.09

#include <stdio.h>
#include <stdarg.h>

#include <VString>
#include <VDebugNew>

// ----------------------------------------------------------------------------
// String function
// ----------------------------------------------------------------------------

// ----- gilgil temp 2015.01.20 -----
/*
static const int DEFAULT_STR_BUF_SIZE = 4096; // gilgil temp 2014.12.09

QString qformat(const char* fmt, ...)
{
  char buf[DEFAULT_STR_BUF_SIZE];
  va_list args;
  va_start(args, fmt);
  vsnprintf(buf, DEFAULT_STR_BUF_SIZE, fmt, args);
  va_end(args);
  return QString(buf);
}
*/
// ----------------------------------

#ifdef GTEST
#include <VDebugNewCancel>
#include <gtest/gtest.h>

TEST( String, ss_to_vs )
{
  std::string ss = "std::string";
  QString     qs = ss.c_str();
  printf("%s\n", qPrintable(qs));
}

TEST( String, vs_to_ss )
{
  QString qs = "test";
  std::string ss = qs.toLatin1().data();
  printf("%s\n", ss.c_str());
}

#endif // GTEST
