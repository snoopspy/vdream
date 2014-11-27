// ----------------------------------------------------------------------------
//
// VDream Component Suite version 9.0
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __V_DESIGN_H__
#define __V_DESIGN_H__

// ----------------------------------------------------------------------------
// VInstance (lazy initialization)
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

// ----------------------------------------------------------------------------
// VPrimitive
// ----------------------------------------------------------------------------
template <class T>
class VPrimitive
{
protected:
	T base;
public:
	VPrimitive() {}
	VPrimitive(const VPrimitive& b) : base(b.base) {}
	VPrimitive(const T& _base) : base(_base) {}
	// ~VPrimitive() {} // do not declare as virtual // gilgil temp 2014.11.27
	// operator T&() { return (T&)m_value; } // gilgil temp 2014.11.27
	operator T&() const { return (T&)base; }
	T* operator &() const { return (T*)&base; }
};

// ----------------------------------------------------------------------------
// VDependencyWith
// ----------------------------------------------------------------------------
template <class T>
class VDependencyWith
{
public:
	/// class T must have static void dependency()
	VDependencyWith()          { T::dependency(); }
	virtual ~VDependencyWith() {}
};

#endif // __V_DESIGN_H__
