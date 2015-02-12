#include <VMyObject>

// ----- gilgil temp 2015.02.01 -----
/*
REGISTER_ABSTRACT_METACLASS(VA, VMyObject)
REGISTER_ABSTRACT_METACLASS(VB, VMyObject)
REGISTER_ABSTRACT_METACLASS(VC, VMyObject)

REGISTER_METACLASS(VAA, VA)
REGISTER_METACLASS(VAB, VA)
REGISTER_METACLASS(VAC, VA)

REGISTER_METACLASS(VBA, VB)
REGISTER_METACLASS(VBB, VB)
REGISTER_METACLASS(VBC, VB)

REGISTER_METACLASS(VCA, VC)
REGISTER_METACLASS(VCB, VC)
REGISTER_METACLASS(VCC, VC)
*/
// ----------------------------------

// ----------------------------------------------------------------------------
// VMyObject
// ----------------------------------------------------------------------------
void VMyObject::explicitLink()
{
  VFactory& factory = VFactory::instance();
  VAA aa; factory.registerMetaObject(aa.metaObject());
  VAB ab; factory.registerMetaObject(ab.metaObject());
  VAC ac; factory.registerMetaObject(ac.metaObject());
  VBA ba; factory.registerMetaObject(ba.metaObject());
  VBB bb; factory.registerMetaObject(bb.metaObject());
  VBC bc; factory.registerMetaObject(bc.metaObject());
  VCA ca; factory.registerMetaObject(ca.metaObject());
  VCB cb; factory.registerMetaObject(cb.metaObject());
  VCC cc; factory.registerMetaObject(cc.metaObject());
}

void VMyObject::foo(int i)
{
  emit send(i);
}

void VMyObject::recv(int i)
{
  LOG_DEBUG("recv i=%d", i);
}

#ifdef GTEST
#include <gtest/gtest.h>

TEST(VMyObjectTest, factoryTest)
{
  VFactory& factory = VFactory::instance();
  VFactory::VMetaObjectList objList = factory.getMetaObjectsByAncestorClassName("VMyObject");
  EXPECT_TRUE(objList.count() == 8);
}

#endif // GTEST
