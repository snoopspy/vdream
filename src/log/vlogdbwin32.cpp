#ifdef WIN32

#include <VLogDBWin32>
#include <winsock2.h>
#include <windows.h> // for OutputDebugString 
#include <VDebugNew>

// REGISTER_METACLASS(VLogDBWin32, VLog) // gilgil temp 2015.02.01

// ----------------------------------------------------------------------------
// VLogDBWin32
// ----------------------------------------------------------------------------
void VLogDBWin32::write(const char* buf, int len)
{
#ifdef UNICODE
  wchar_t wcs[len + 2];
  mbstowcs(wcs, buf, len);
  wcs[len] = '\n';
  wcs[len + 1] = '\0';
  OutputDebugString(wcs);

  // ----- gilgil temp 2014.12.25 -----
  /*
  std::wstring ws = char_to_wcs(buf, len);
  OutputDebugString(ws.c_str());
  OutputDebugString(L"\n");
  */
  // ----------------------------------
#else
  OutputDebugString(buf);
  OutputDebugString("\n");
#endif // UNICODE
}

VLog* VLogDBWin32::createByURI(const QString& uri)
{
  if (uri == "dbwin32")
  {
    return new VLogDBWin32;
  }
  return NULL;
}

#endif // WIN32
