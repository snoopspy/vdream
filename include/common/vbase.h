// ----------------------------------------------------------------------------
//
// VDream Component Suite version 9.0
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __V_BASE_H__
#define __V_BASE_H__

// ----------------------------------------------------------------------------
// VBase
// ----------------------------------------------------------------------------
template <class T>
class VBase
{
protected:
	T base;
public:
	VBase()                              {                   }
	VBase(const VBase& b) : base(b.base) {                   }
	VBase(const T& _base) : base(_base)  {                   }
	operator T&() const                  { return (T&)base;  }
	T* operator &() const                { return (T*)&base; }
};

#endif // __V_BASE_H__
