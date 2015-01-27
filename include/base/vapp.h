// ----------------------------------------------------------------------------
//
// VDream Component Suite version 9.0
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __V_APP_H__
#define __V_APP_H__

// #include <VXmlDoc> // gilgil temp 2015.01.27
#include <VLogFactory>

// ----------------------------------------------------------------------------
// VApp
// ----------------------------------------------------------------------------
class VApp
{
private: // singleton
  VApp();
  virtual ~VApp();

// ----- gilgil temp 2014.12.25 -----
/*
protected:
  int    m_argc;
  char** m_argv;

public:
  void   setArguments(int argc, char* argv[]) { m_argc = argc; m_argv = argv; }
  int    argc()                               { return m_argc;                }
  char** argv()                               { return m_argv;                }

public:
  static QString fileName();                   > QCoreApplication::applicationFilePath()
  static QString _filePath();                  > QCoreApplication::applicationDirPath()
  static QString currentPath();                > QDir::currentPath()
  static bool    setCurrentPath(QString path); > QDir::setCurrent(path)
*/
// ----------------------------------

public:
#ifdef QT_GUI_LIB
  static void initialize(bool path = true, bool xml = true, QString uri = "udp;file://log/");
#else // QT_GUI_LIB
  static void initialize(bool path = true, bool xml = true, QString uri = "stdout;udp;file://log/");
#endif // QT_GUI_LIB

  static void finalize(bool xml = true);

public:
  static VApp& instance()
  {
    static VApp app;
    return app;
  }

private:
  Q_DISABLE_COPY(VApp)
};

#endif // __V_APP_H__
