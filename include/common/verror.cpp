#include <cxxabi.h>
#include <QDebug>
#include "verror.h"

VError::VError(const VError& rhs)
{
  ti = (std::type_info*)&typeid(rhs);
  msg = rhs.msg;
  code = rhs.code;
}

VError& VError::operator = (const VError& rhs)
{
  if (code == OK)
  {
    ti = (std::type_info*)&typeid(rhs);
    msg = rhs.msg;
    code = rhs.code;
  }
  return *this;
}

const char* VError::className()
{
  const char* name = ti->name();
  char *res = abi::__cxa_demangle(name, 0, 0, NULL);
  //char *res = abi::__cxa_demangle(typeid(*this).name(), 0, 0, NULL);
  return res;
}

void VError::clear()
{
  ti = (std::type_info*)&typeid(*this);
  msg = "";
  code = OK;
}

void VError::dump()
{
  qDebug() << className() << msg << code;
}

void VError::dump(const char* file, const int line, const char* func)
{
  QString s = QString("[%1:%2] %3() %4 %5:%6").arg(file).arg(line).arg(func).arg(className()).arg(msg).arg(code);
  qDebug() << s;
}

void VError::debug(const char* file, const int line, const char* func)
{
  Q_UNUSED(file)
  Q_UNUSED(line)
  Q_UNUSED(func)
}

#ifdef GTEST
#include <gtest/gtest.h>
#include <QDebug>

class VErrTest : public ::testing::Test {};

class ObjError : public VError
{
public:
  enum {
    OBJ_ERR = 999
  };

public:
  VERROR_CTOR(ObjError)
};

TEST_F(VErrTest, commonTest)
{
  VError error;
  error.dump();
  EXPECT_EQ(error.ti, &typeid(VError));

  ObjError objError;
  objError.dump();
  EXPECT_EQ(objError.ti, &typeid(ObjError));
}

TEST_F(VErrTest, clearTest)
{
  VError error;
  error.clear();
  error.dump();
  EXPECT_EQ(error.ti, &typeid(VError));

  ObjError objError;
  objError.clear();
  objError.dump();
  EXPECT_EQ(objError.ti, &typeid(ObjError));
}

TEST_F(VErrTest, copyConTest)
{
  {
    VError error = ObjError();
    error.dump();
    EXPECT_TRUE(error.ti == &typeid(ObjError));
  }
  {
    VError error = ObjError("OBJ_ERR", ObjError::OBJ_ERR);
    error.dump();
    EXPECT_TRUE(error.ti == &typeid(ObjError));
  }
}

TEST_F(VErrTest, assignTest)
{
  {
    VError error;
    error = ObjError();
    error.dump();
    EXPECT_TRUE(error.ti == &typeid(ObjError));
  }
  {
    VError error;
    error = ObjError("OBJ_ERR", ObjError::OBJ_ERR);
    error.dump();
    EXPECT_TRUE(error.ti == &typeid(ObjError));
  }
}

TEST_F(VErrTest, macroTest)
{
  VError error;
  SET_ERROR(VError, "not closed state", VError::NOT_CLOSED_STATE);
  EXPECT_TRUE(error.ti == &typeid(VError));

  SET_ERROR(ObjError, "OBJ_ERROR", ObjError::OBJ_ERR);
  EXPECT_TRUE(error.ti == &typeid(VError));

  error.clear();
  SET_ERROR(ObjError, "OBJ_ERROR", ObjError::OBJ_ERR);
  EXPECT_TRUE(error.ti == &typeid(ObjError));
}

#endif // GTEST
