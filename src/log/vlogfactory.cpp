#include <VLogFactory>
#include <VXmlDoc>
#include <VLogDBWin32>
#include <VLogFile>
#include <VLogHttp>
#include <VLogNull>
#include <VLogStderr>
#include <VLogStdout>
#include <VLogUdp>
#include <VLogList>
#include <VDebugNew>

// ----------------------------------------------------------------------------
// VLogFactory
// ----------------------------------------------------------------------------
void VLogFactory::explicitLink()
{
  VFactory& factory = VFactory::instance();
#ifdef _WIN32Z
  VLogDBWin32 logDBWin32; factory.registerMetaObject(logDBWin32.metaObject());
#endif // _WIN32
  VLogFile    logFile;   factory.registerMetaObject(logFile.metaObject());
  VLogHttp    logHTTP;   factory.registerMetaObject(logHTTP.metaObject());
  VLogNull    logNull;   factory.registerMetaObject(logNull.metaObject());
  VLogStderr  logStderr; factory.registerMetaObject(logStderr.metaObject());
  VLogStdout  logStdout; factory.registerMetaObject(logStdout.metaObject());
  VLogUdp     logUdp;    factory.registerMetaObject(logUdp.metaObject());
  VLogList    logList;   factory.registerMetaObject(logList.metaObject());
}

VLog* VLogFactory::createByClassName(const QString& className)
{
  return dynamic_cast<VLog*>(VFactory::instance().createObjectByClassName(className)); // gilgil temp 2015.02.01
}

VLog* VLogFactory::createByDefaultDoc(const QString& path)
{
  return dynamic_cast<VLog*>(VFactory::instance().createObjectByDefaultDoc(path)); // gilgil temp 2015.02.01
}

VLog* VLogFactory::createByURI(const QString& uri)
{
  VFactory& factory = VFactory::instance();
  VFactory::VMetaObjectList mobjList = factory.getMetaObjectsByAncestorClassName("VLog");

  VLog* ret = NULL;
  foreach (const QMetaObject* mobj, mobjList)
  {
    VLog* _log = dynamic_cast<VLog*>(factory.createObjectByClassName(mobj->className()));
    if (_log == NULL)
    {
      LOG_FATAL("can not create log for '%s'", mobj->className());
      continue;
    }
    VLog* log = _log->createByURI(uri);
    delete _log;
    if (log != NULL)
    {
      ret = log;
      break;
    }
  }
  if (ret == NULL)
  {
    LOG_FATAL("can not create log for '%s'", qPrintable(uri));
  }
  return ret;
}

VLog* VLogFactory::createDefaultLog()
{
  return new VLogUdp;
}
