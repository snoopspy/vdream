#include <VBase>
#include <VDebugNew>

// ----- gilgil temp 2014.12.25 -----
/*
#ifdef linux
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

// ----------------------------------------------------------------------------
// VState
// ----------------------------------------------------------------------------
VState::VState(const QString s)
{
  if (s == "None")         value = None;
  else if (s == "Closed")  value = Closed;
  else if (s == "Opening") value = Opening;
  else if (s == "Opened")  value = Opened;
  else if (s == "Closing") value = Closing;
  else value = None;
}

QString VState::str() const
{
  QString res;
  switch (value)
  {
    case None:    res = "None";    break;
    case Closed:  res = "Closed";  break;
    case Opening: res = "Opening"; break;
    case Opened:  res = "Opened";  break;
    case Closing: res = "Closing"; break;
    default:      res = "None";    break;
  }
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
