#include <VLogStdout>
#include <VDebugNew>

// REGISTER_METACLASS(VLogStdout, VLog) // gilgil temp 2015.02.01

// ----------------------------------------------------------------------------
// VLogStdout
// ----------------------------------------------------------------------------
VLogStdout::VLogStdout()
{
  autoFlush = true;
}

VLogStdout::~VLogStdout()
{
}

void VLogStdout::write(const char* buf, int len)
{
  Q_UNUSED(len)
  printf("%s\n", buf);
  if (autoFlush) fflush(stdout);
}

VLog* VLogStdout::createByURI(const QString& uri)
{
  if (uri == "stdout")
  {
    return new VLogStdout;
  }
  return NULL;
}

void VLogStdout::load(VXml xml)
{
  VLog::load(xml);

  autoFlush = xml.getBool("autoFlush", autoFlush);
}

void VLogStdout::save(VXml xml)
{
  VLog::save(xml);

  xml.setBool("autoFlush", autoFlush);
}
