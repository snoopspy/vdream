// ----------------------------------------------------------------------------
//
// VDream Component Suite version 9.1
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __V_INSTANCE_H__
#define __V_INSTANCE_H__

// ----------------------------------------------------------------------------
// VInstance
// ----------------------------------------------------------------------------
template <class T>
class VInstance : private T
{
public:
	inline static T& instance()
	{
		static VInstance<T> g_instance;
		return  g_instance;
	}
};

#endif // __V_INSTANCE_H__
