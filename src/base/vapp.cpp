#include <VApp>
#include <VDebugNew>

// ----------------------------------------------------------------------------
// VApp
// ----------------------------------------------------------------------------
VApp::VApp()
{
}

VApp::~VApp()
{
}

// ----- gilgil temp 2014.12.25 -----
/*
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif // NOMINMAX
#include <winsock2.h>
#include <windows.h>

QString VApp::fileName()
{
  char buf[VBase::BUF_SIZE];
  DWORD res = GetModuleFileNameA(NULL, buf, VBase::BUF_SIZE);
  if (res == VBase::BUF_SIZE && GetLastError() == ERROR_INSUFFICIENT_BUFFER)
  {
    return "";
  }
  return QString(buf);
}
#endif // _WIN32

#ifdef __linux__

#ifndef MIN
#define MIN(a,b) (((a)<(b))?(a):(b))
#endif // MIN

QString VApp::fileName()
{
  static QString fileName;
  if (fileName == "")
  {
    char buf[VBase::BUF_SIZE];
    memset(buf, 0, VBase::BUF_SIZE);
    char tmp[256];
    sprintf(tmp, "/proc/%d/exe", getpid());
    int res = MIN(readlink(tmp, buf, VBase::BUF_SIZE), VBase::BUF_SIZE - 1);
    if(res >= 0)
      buf[res] = '\0';
    fileName = QString(buf);
  }
  return fileName;
}
#endif // __linux__

QString VApp::_filePath()
{
  QString res = QFileInfo(VApp::fileName()).path();
  if (!res.endsWith('/') && !res.endsWith('\\')) res += QDir::separator();
  return res;
}

QString VApp::currentPath()
{
  QString res = QDir::currentPath();
  if (!res.endsWith('/') && !res.endsWith('\\'))
    res += QDir::separator();
  return res;
}

bool VApp::setCurrentPath(QString path)
{
  return QDir::setCurrent(path);
}
*/
// ----------------------------------

void VApp::initialize(bool path, bool xml, QString uri)
{
  //---------------------------------------------------------------------------
  // set current path
  //---------------------------------------------------------------------------
  if (path)
  {
    // VApp::setCurrentPath(VApp::_filePath()); // gilgil temp 2014.12.25
    QDir::setCurrent(QCoreApplication::applicationDirPath());
  }

  //---------------------------------------------------------------------------
  // load default xml file
  //---------------------------------------------------------------------------
  if (xml)
  {
    QString fileName = VXmlDoc::defaultFileName();
    if (QFile::exists(fileName))
      VXmlDoc::instance().loadFromFile(fileName);
  }

  //---------------------------------------------------------------------------
  // load default log
  //---------------------------------------------------------------------------
  if (uri != "")
  {
    VLogFactory::explicitLink();
    VLog* log = VLogFactory::createByDefaultDoc("log");
    if (log == NULL)
    {
      log = VLogFactory::createByURI(uri);
    }
    if (log == NULL)
    {
      printf("***********\n");
      printf("log is null\n");
      printf("***********\n");
      return;
    }
    log->saveToDefaultDoc("log");
    VLog::changeLog(log);
  }
}

void VApp::finalize(bool xml)
{
  //---------------------------------------------------------------------------
  // save default xml file
  //---------------------------------------------------------------------------
  if (xml)
  {
    QString fileName = VXmlDoc::defaultFileName();
    VXmlDoc::instance().saveToFile(fileName);
  }
}

#ifdef GTEST
#include <VDebugNewCancel>
#include <gtest/gtest.h>

class AppTest : public ::testing::Test
{
  QCoreApplication* app;
  virtual void SetUp()
  {
    int argc = 0;
    app = new QCoreApplication(argc, NULL);
  }

  virtual void TearDown()
  {
    delete app;
  }
};

TEST_F( AppTest, filePathTest )
{
  QString filePath = QCoreApplication::applicationFilePath();
  qDebug() << "filePath=" << filePath;
  QString fileName = QFileInfo(filePath).fileName();
  qDebug() << "fileName=" << fileName;
}

TEST_F( AppTest, pathTest )
{
  QString path = QDir::currentPath();

  {
    QString path = QDir::currentPath();
    QString fileName = "__current__.txt";

    qDebug() << "QDir::currentPath() =" << path;
    EXPECT_TRUE( QDir::setCurrent(path) == true );

    QFile file(fileName);
    EXPECT_TRUE( file.open(QFile::WriteOnly) );
    file.close();
    EXPECT_TRUE( QFile::exists(fileName) );
    EXPECT_TRUE( QFile::remove(fileName) );
  }
  {
    QString path = "/";
    QString fileName = "__root__.txt";

    qDebug() << "rootPath =" << path;
    EXPECT_TRUE( QDir::setCurrent(path) == true );

    QFile file(fileName);
    EXPECT_TRUE( file.open(QFile::WriteOnly) );
    file.close();
    EXPECT_TRUE( QFile::exists(fileName) );
    EXPECT_TRUE( QFile::remove(fileName) );
  }
  {
    QString path = QCoreApplication::applicationDirPath();
    QString fileName = "__application__.txt";

    qDebug() << "QCoreApplication::applicationDirPath() =" << path;
    EXPECT_TRUE( QDir::setCurrent(path) == true );

    QFile file(fileName);
    EXPECT_TRUE( file.open(QFile::WriteOnly) );
    file.close();
    EXPECT_TRUE( QFile::exists(fileName) );
    EXPECT_TRUE( QFile::remove(fileName) );
  }

  QDir::setCurrent(path);
}

#endif // GTEST
