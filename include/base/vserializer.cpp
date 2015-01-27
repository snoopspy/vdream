#include <assert.h>
#include <stdio.h> // for printf
#include "vserializer.h"

bool VStrSerializer::load(VObject* object, QMetaProperty mpro, VRep& rep)
{
  const char* propName = mpro.name();
  QVariant value = rep[propName];
  object->setProperty(propName, value);
  return true;
}

bool VStrSerializer::save(VObject* object, QMetaProperty mpro, VRep& rep)
{
  const char* propName = mpro.name();
  QVariant value = object->property(propName);
  if (!(QString(propName) == "objectName" && value == ""))
    rep[propName] = value;
  return true;
}

#ifdef QT_GUI_LIB
bool VStrSerializer::createTreeWidgetItems(VTreeWidgetItem* parent, VObject* object, QMetaProperty mpro)
{
  VTreeWidgetItemStr* item = new VTreeWidgetItemStr(parent, object, mpro);
  item->initialize();
  return true;
}
#endif // QT_GUI_LIB

bool VBoolSerializer::load(VObject* object, QMetaProperty mpro, VRep& rep)
{
  int userType = mpro.userType();
  if (userType != QVariant::Bool) return false;
  const char* propName = mpro.name();
  bool value = rep[propName].toBool();
  object->setProperty(propName, value);
  return true;
}

bool VBoolSerializer::save(VObject* object, QMetaProperty mpro, VRep& rep)
{
  int userType = mpro.userType();
  if (userType != QVariant::Bool) return false;
  const char* propName = mpro.name();
  bool value = object->property(propName).toBool();
  rep[propName] = value;
  return true;
}

#ifdef QT_GUI_LIB
bool VBoolSerializer::createTreeWidgetItems(VTreeWidgetItem* parent, VObject* object, QMetaProperty mpro)
{
  int userType = mpro.userType();
  if (userType != QVariant::Bool) return false;
  VTreeWidgetItemBool* item = new VTreeWidgetItemBool(parent, object, mpro);
  item->initialize();
  return true;
}
#endif // QT_GUI_LIB

bool VEnumSerializer::load(VObject* object, QMetaProperty mpro, VRep& rep)
{
  if (!mpro.isEnumType()) return false;
  QMetaEnum menum = mpro.enumerator();
  const char* propName = mpro.name();
  QString from = rep[propName].toString();
  QVariant to = menum.keyToValue(qPrintable(from));
  object->setProperty(propName, to);
  return true;
}

bool VEnumSerializer::save(VObject* object, QMetaProperty mpro, VRep& rep)
{
  if (!mpro.isEnumType()) return false;
  QMetaEnum menum = mpro.enumerator();
  const char* propName = mpro.name();
  QVariant value = object->property(propName);
  int index = value.toInt();
  QString to = menum.key(index);
  rep[propName] = to;
  return true;
}

#ifdef QT_GUI_LIB
bool VEnumSerializer::createTreeWidgetItems(VTreeWidgetItem* parent, VObject* object, QMetaProperty mpro)
{
  if (!mpro.isEnumType()) return false;
  VTreeWidgetItemEnum* item = new VTreeWidgetItemEnum(parent, object, mpro);
  item->initialize();
  return true;
}
#endif // QT_GUI_LIB

QVariant VConvertSerializer::convert(QVariant from, int type)
{
  QVariant to(type, NULL);

  void* fromData     = from.data();
  int   fromUserType = from.userType();
  void* toData       = to.data();
  int   toUserType   = to.userType();
  bool res = QMetaType::convert(fromData, fromUserType, toData, toUserType);
  if (!res)
  {
    printf("VObject::load QMetaType::convert return false\n");
  }
  return to;
}

bool VConvertSerializer::load(VObject* object, QMetaProperty mpro, VRep& rep)
{
  int userType = mpro.userType();
  if (!QMetaType::hasRegisteredConverterFunction(QVariant::String, userType)) return false;
  const char* propName = mpro.name();
  QString from = rep[propName].toString();
  QVariant to = convert(from, userType);
  object->setProperty(propName, to);
  return true;
}

bool VConvertSerializer::save(VObject* object, QMetaProperty mpro, VRep& rep)
{
  int userType = mpro.userType();
  if (!QMetaType::hasRegisteredConverterFunction(userType, QVariant::String)) return false;
  const char* propName = mpro.name();
  QVariant from = object->property(propName);
  QVariant to = convert(from, QVariant::String);
  rep[propName] = to;
  return true;
}

#ifdef QT_GUI_LIB
bool VConvertSerializer::createTreeWidgetItems(VTreeWidgetItem* parent, VObject* object, QMetaProperty mpro)
{
  int userType = mpro.userType();
  if (!QMetaType::hasRegisteredConverterFunction(userType, QVariant::String)) return false;
  VTreeWidgetItemStr* item = new VTreeWidgetItemStr(parent, object, mpro);
  item->initialize();
  return true;
}
#endif // QT_GUI_LIB

bool VObjectSerializer::load(VObject* object, QMetaProperty mpro, VRep& rep)
{
  int userType = mpro.userType();
  if (userType != qMetaTypeId<VObject*>()) return false;
  const char* propName = mpro.name();
  VObject* childObj = object->property(propName).value<VObject*>();
  assert(childObj != NULL);
  VRep childRep = rep[propName].toMap();
  childObj->load(childRep);
  return true;
}

bool VObjectSerializer::save(VObject* object, QMetaProperty mpro, VRep& rep)
{
  int userType = mpro.userType();
  if (userType != qMetaTypeId<VObject*>()) return false;
  const char* propName = mpro.name();
  VObject* childObj = object->property(propName).value<VObject*>();
  VRep childRep;
  childObj->save(childRep);
  rep[propName] = childRep;
  return true;
}

#ifdef QT_GUI_LIB
bool VObjectSerializer::createTreeWidgetItems(VTreeWidgetItem* parent, VObject* object, QMetaProperty mpro)
{
  int userType = mpro.userType();
  if (userType != qMetaTypeId<VObject*>()) return false;
  const char* propName = mpro.name();
  VObject* childObj = object->property(propName).value<VObject*>();
  assert(childObj != NULL);
  VTreeWidgetItemObject* item = new VTreeWidgetItemObject(parent, childObj, VTreeWidgetItemObject::SHOW_OBJECT_NAME);
  item->initialize();
  childObj->createTreeWidgetItems(item);
  return true;
}
#endif // QT_GUI_LIB

bool VObjectListSerializer::load(VObject* object, QMetaProperty mpro, VRep& rep)
{
  int userType = mpro.userType();
  if (userType != qMetaTypeId<VObjectList*>()) return false;
  const char* propName = mpro.name();
  VObjectList* childObjList = object->property(propName).value<VObjectList*>();
  assert(childObjList != NULL);
  VRep childRepList = rep[propName].toMap();
  for (VRep::iterator it = childRepList.begin(); it != childRepList.end(); it++)
  {
    VRep childRep = it->toMap();
    VObject* vobj = childObjList->createObject();
    vobj->load(childRep);
    childObjList->push_back(vobj);
  }
  return true;
}

bool VObjectListSerializer::save(VObject* object, QMetaProperty mpro, VRep& rep)
{
  int userType = mpro.userType();
  if (userType != qMetaTypeId<VObjectList*>()) return false;
  const char* propName = mpro.name();
  VObjectList* childObjtList = object->property(propName).value<VObjectList*>();
  assert(childObjtList != NULL);
  VRep childRepList;
  int i = 0;
  foreach (VObject* childObj, *childObjtList)
  {
    VRep childRep;
    childObj->save(childRep);
    childRepList[QString::number(i)] = childRep;
    i++;
  }
  rep[propName] = childRepList;
  return true;
}

#ifdef QT_GUI_LIB
bool VObjectListSerializer::createTreeWidgetItems(VTreeWidgetItem* parent, VObject* object, QMetaProperty mpro)
{
  int userType = mpro.userType();
  if (userType != qMetaTypeId<VObjectList*>()) return false;
  const char* propName = mpro.name();
  VObjectList* childObjectList = object->property(propName).value<VObjectList*>();
  assert(childObjectList != NULL);
  VTreeWidgetItemObjectList* item = new VTreeWidgetItemObjectList(parent, object, mpro);
  item->initialize();
  foreach (VObject* childObj, *childObjectList)
  {
    VTreeWidgetItemObject* childItem = new VTreeWidgetItemObject(item, childObj, VTreeWidgetItemObject::SHOW_DEL_BUTTON);
    childItem->initialize();
    childObj->createTreeWidgetItems(childItem);
  }
  return true;
}
#endif // QT_GUI_LIB

bool VSerializerMgr::load(VObject* object, QMetaProperty mpro, VRep& rep)
{
  int count = serializerList.count();
  for (int i = count - 1; i >= 0; i--)
  {
    VSerializer* serializer = serializerList.at(i);
    if (serializer->load(object, mpro, rep))
      return true;
  }
  printf("VSerializerMgr::load return false object=%s\n", object->metaObject()->className());
  return false;
}

bool VSerializerMgr::save(VObject* object, QMetaProperty mpro, VRep& rep)
{
  int count = serializerList.count();
  for (int i = count - 1; i >= 0; i--)
  {
    VSerializer* serializer = serializerList.at(i);
    if (serializer->save(object, mpro, rep))
      return true;
  }
  printf("VSerializerMgr::save return false class=%s\n", object->metaObject()->className());
  return false;
}

#ifdef QT_GUI_LIB
bool VSerializerMgr::createTreeWidgetItems(VTreeWidgetItem* parent, VObject* object, QMetaProperty mpro)
{
  int count = serializerList.count();
  for (int i = count - 1; i >= 0; i--)
  {
    VSerializer* serializer = serializerList.at(i);
    if (serializer->createTreeWidgetItems(parent, object, mpro))
      return true;
  }
  printf("VSerializerMgr::createTreeWidgetItems return false class=%s\n", object->metaObject()->className());
  return false;
}
#endif // QT_GUI_LIB

void VSerializerMgr::_initialize()
{
  static VStrSerializer        strSerializer;
  static VBoolSerializer       boolSerializer;
  static VEnumSerializer       enumSerializer;
  static VConvertSerializer    convertSerializer;
  static VObjectSerializer     objectSerializer;
  static VObjectListSerializer objectListSerializer;

  VSerializerMgr& mgr = VSerializerMgr::instance();
  mgr.serializerList.push_back(&strSerializer);
  mgr.serializerList.push_back(&boolSerializer);
  mgr.serializerList.push_back(&enumSerializer);
  mgr.serializerList.push_back(&convertSerializer);
  mgr.serializerList.push_back(&objectSerializer);
  mgr.serializerList.push_back(&objectListSerializer);
}

VSerializerMgr& VSerializerMgr::instance()
{
  static VSerializerMgr serializerMgr;
  return serializerMgr;
}
