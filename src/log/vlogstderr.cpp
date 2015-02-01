#include <VLogStderr>
#include <VDebugNew>

// REGISTER_METACLASS(VLogStderr, VLog) // gilgil temp 2015.02.01

// ----------------------------------------------------------------------------
// VLogStderr
// ----------------------------------------------------------------------------
VLogStderr::VLogStderr()
{
  autoFlush = true;
}

VLogStderr::~VLogStderr()
{
}

void VLogStderr::write(const char* buf, int len)
{
  Q_UNUSED(len)
  fprintf(stderr, "%s\n", buf);
  if (autoFlush) fflush(stderr);
}

VLog* VLogStderr::createByURI(const QString& uri)
{
  if (uri == "stderr")
  {
    return new VLogStderr;
  }
  return NULL;
}

void VLogStderr::load(VXml xml)
{
  VLog::load(xml);

  autoFlush = xml.getBool("autoFlush", autoFlush);
}

void VLogStderr::save(VXml xml)
{
  VLog::save(xml);

  xml.setBool("autoFlush", autoFlush);
}
