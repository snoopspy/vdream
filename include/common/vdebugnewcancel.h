// ----------------------------------------------------------------------------
//
// VDream Component Suite version 9.1
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __V_DEBUG_NEW_CANCEL_H__
#define __V_DEBUG_NEW_CANCEL_H__

#ifdef _DEBUG

#undef debug_new
#define debug_new new
#undef malloc
#undef free

#endif // _DEBUG

#endif // __V_DEBUG_NEW_CANCEL_H__

