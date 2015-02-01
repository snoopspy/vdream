#include <VLogNull>
#include <VDebugNew>

// REGISTER_METACLASS(VLogNull, VLog) // gilgil temp 2015.02.01

// ----------------------------------------------------------------------------
// VLogNull
// ----------------------------------------------------------------------------
VLog* VLogNull::createByURI(const QString& uri)
{
  if (uri == "null")
  {
    return new VLogNull;
  }
  return NULL;
}
