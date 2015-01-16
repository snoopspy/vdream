// ----------------------------------------------------------------------------
//
// VDream Component Suite version 9.0.1
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __V_FILE_H__
#define __V_FILE_H__

#include <QFile>
#include <VBase>
#include <VRwObject>

// ----------------------------------------------------------------------------
// VFile
// ----------------------------------------------------------------------------
class VFile : public VRwObject, public VBase<QFile>
{
public:
  VFile(void* owner = NULL);
  VFile(const QString& fileName);
  VFile(const QString& fileName, QIODevice::OpenMode mode);
  virtual ~VFile();

public:
  QString             fileName;
  QIODevice::OpenMode mode;

protected:
  bool doOpen();
  bool doClose();
  int  doRead(char* buf,  int size);
  int  doWrite(char* buf, int size);

public:
  static bool createFolder(QString folder);

public:
  virtual void load(VXml xml);
  virtual void save(VXml xml);
};

// ----------------------------------------------------------------------------
// FileError
// ----------------------------------------------------------------------------
class VFileError : public VError
{
public:
  enum {
    END_OF_FILE,
    ERROR_IN_OPEN_FILE,
    ERROR_IN_READ_FILE,
    ERROR_IN_WRITE_FILE,
    FILE_NOT_EXIST,
    ERROR_IN_FILESEEK,
    FILENAME_NOT_SPECIFIED,
    INVALID_FILENAME,
  };
};

// ----------------------------------------------------------------------------
// FileError code
// ----------------------------------------------------------------------------

#endif // __V_FILE_H__

