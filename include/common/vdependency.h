// ----------------------------------------------------------------------------
//
// VDream Component Suite version 9.0
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __V_DENDENCY_H__
#define __V_DENDENCY_H__

// ----------------------------------------------------------------------------
// VDependency
// ----------------------------------------------------------------------------
template <class T>
class VDependency
{
public:
	/// class T must have static void dependency()
	VDependency() { T::dependency(); }
};

#endif // __V_DENDENCY_H__
