// ----------------------------------------------------------------------------
//
// VDream Component Suite version 9.1
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __V_PRIMITIVE_H__
#define __V_PRIMITIVE_H__

// ----------------------------------------------------------------------------
// VPrimitive
// ----------------------------------------------------------------------------
template <class T>
class VPrimitive
{
protected:
  T primitive;
public:
  VPrimitive()                                                 {}
  VPrimitive(const VPrimitive& rhs) : primitive(rhs.primitive) {}
  VPrimitive(const T& _primitive) : primitive(_primitive)      {}
  operator T&() const                                          { return (T&)primitive;  }
  T* operator &() const                                        { return (T*)&primitive; }
};

#endif // __V_PRIMITIVE_H__
