#include <VLogStderr>
#include <VDebugNew>

REGISTER_METACLASS(VLogStderr, VLog)

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

void VLogStderr::load(VRep& rep)
{
  VLog::load(xml);

  autoFlush = rep.getBool("autoFlush", autoFlush);
}

void VLogStderr::save(VRep& rep)
{
  VLog::save(xml);

  rep.setBool("autoFlush", autoFlush);
}
