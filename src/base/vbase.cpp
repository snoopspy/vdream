#include <VBase>
#include <VDebugNew>

// ----- gilgil temp 2014.12.25 -----
/*
#ifdef __linux__
#include <cxxabi.h> // for __cxa_demangle
#endif // lunux
*/
#include <cxxabi.h> // for __cxa_demangle
// ----------------------------------

#include <VDebugNew>

// ----------------------------------------------------------------------------
// vdream Version
// ----------------------------------------------------------------------------
#ifdef _DEBUG
const char* VBase::VDREAM_VERSION = "VDream 9.1 Debug   Build( " __DATE__ " " __TIME__ " )";
#else // RELEASE
const char* VBase::VDREAM_VERSION = "VDream 9.1 Release Build( " __DATE__ " " __TIME__ " )";
#endif // _DEBUG

// ----------------------------------------------------------------------------
// Class
// ----------------------------------------------------------------------------
const char* VBase::getClassName(const char* value)
{
  int status;
  char* res = abi::__cxa_demangle(value, 0, 0, &status);
  char* p = strstr(res, "::");
  if (p != NULL) res = p + 2;
  return res;
}

#ifdef GTEST
#include <VDebugNewCancel>
#include <gtest/gtest.h>

TEST( BaseTest, versionTest )
{
  qDebug() << VBase::VDREAM_VERSION;
}

TEST( BaseTest, macroTest )
{
  qDebug() << "__DATE__    =" << __DATE__;
  qDebug() << "__TIME__    =" << __TIME__;
  qDebug() << "__FILE__    =" << __FILE__;
}

TEST( BaseTest, classNameTest )
{
  class MyObject {};
  MyObject obj;
  QString className = VBase::getClassName(typeid(obj).name());
  qDebug() << "MyObject class name is " << className;
  EXPECT_TRUE( className == "MyObject" );
}

#endif // GTEST
