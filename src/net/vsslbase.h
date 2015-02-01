// ----------------------------------------------------------------------------
//
// VDream Component Suite version 9.01
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __V_SSL_BASE_H__
#define __V_SSL_BASE_H__

#include <VError>
#include <VLog>
#ifdef WIN32
#define _WINSOCKAPI_ // for compiler error in openssl module
#endif // WIN32
#include <openssl/ssl.h>

// ----------------------------------------------------------------------------
// VSslBase
// ----------------------------------------------------------------------------
class VSslBase
{
public:
  static const int DEFAULT_SSL_PORT        = 443;
  static const int DEFAULT_SSL_PROXY_PORT  = 4433;

private: // singleton
  VSslBase();
  virtual ~VSslBase();

protected:
  static int numLock;
  static VCS *lockCs;

protected:
  static unsigned long threadIdCallback(void);
  static void lockingCallback(int mode, int type, const char* file, int line);

public:
  static VSslBase& instance();
};

// ----------------------------------------------------------------------------
// VSslMethodType
// ----------------------------------------------------------------------------
class VSslMethodType
{
public:
  enum _VSslMethodType
  {
    mtNone,    // 0
    mtSSLv2,   // 1
    mtSSLv3,   // 2
    mtSSLv23,  // 3
    mtTLSv1,   // 4
    mtTLSv1_1, // 5
    mtTLSv1_2, // 6
    mtDTLSv1   // 7
  };

protected:
  _VSslMethodType value;

public:
  VSslMethodType()                            {                      } // default ctor
  VSslMethodType(const _VSslMethodType value) { this->value = value; } // conversion ctor
  operator _VSslMethodType() const            { return value;        } // cast operator

public:
  VSslMethodType(const int i)                 { value = (_VSslMethodType)i; }
  VSslMethodType(const QString s);
  QString str() const;
};

// ----------------------------------------------------------------------------
// VSslError
// ----------------------------------------------------------------------------
class VSslError : public VError
{
public:
  enum {
    INVALID_SSL_METHOD = VERR_CATEGORY_SSL,
    IN_BIO_S_FILE,
    IN_BIO_READ_FILENAME,
    IN_PEM_READ_BIO_PRIVATEKEY,
    IN_PEM_READ_BIO_X509_AUX,
    IN_SSL_CTX_USE_CERTIFICATE,
    SSL_CTX_USER_PRIVATEKEY,
    SSL_CTX_CHECK_PRIVATEKEY
  };
  VERROR_CTOR(VSslError)
};

#endif // __V_SSL_BASE_H__
