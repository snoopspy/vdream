#ifndef VSERIALIZER_H
#define VSERIALIZER_H

#include <QList>
#include <QMetaProperty>
#include "vobject.h"
#include "vwidget.h"

class VSerializer
{
public:
  virtual bool load(VObject* object, QMetaProperty mpro, VRep& rep) = 0;
  virtual bool save(VObject* object, QMetaProperty mpro, VRep& rep) = 0;
#ifdef QT_GUI_LIB
  virtual bool createTreeWidgetItems(VTreeWidgetItem* parent, VObject* object, QMetaProperty mpro) = 0;
#endif // QT_GUI_LIB
};

class VStrSerializer : public VSerializer
{
public:
  virtual bool load(VObject* object, QMetaProperty mpro, VRep& rep);
  virtual bool save(VObject* object, QMetaProperty mpro, VRep& rep);
#ifdef QT_GUI_LIB
  virtual bool createTreeWidgetItems(VTreeWidgetItem* parent, VObject* object, QMetaProperty mpro);
#endif // QT_GUI_LIB
};

class VBoolSerializer : public VSerializer
{
public:
  virtual bool load(VObject* object, QMetaProperty mpro, VRep& rep);
  virtual bool save(VObject* object, QMetaProperty mpro, VRep& rep);
#ifdef QT_GUI_LIB
  virtual bool createTreeWidgetItems(VTreeWidgetItem* parent, VObject* object, QMetaProperty mpro);
#endif // QT_GUI_LIB
};

class VEnumSerializer : public VSerializer
{
public:
  virtual bool load(VObject* object, QMetaProperty mpro, VRep& rep);
  virtual bool save(VObject* object, QMetaProperty mpro, VRep& rep);
#ifdef QT_GUI_LIB
  virtual bool createTreeWidgetItems(VTreeWidgetItem* parent, VObject* object, QMetaProperty mpro);
#endif // QT_GUI_LIB
};

class VConvertSerializer : public VSerializer
{
public:
  static QVariant convert(QVariant from, int type);

public:
  virtual bool load(VObject* object, QMetaProperty mpro, VRep& rep);
  virtual bool save(VObject* object, QMetaProperty mpro, VRep& rep);
#ifdef QT_GUI_LIB
  virtual bool createTreeWidgetItems(VTreeWidgetItem* parent, VObject* object, QMetaProperty mpro);
#endif // QT_GUI_LIB
};

class VObjectSerializer : public VSerializer
{
public:
  virtual bool load(VObject* object, QMetaProperty mpro, VRep& rep);
  virtual bool save(VObject* object, QMetaProperty mpro, VRep& rep);
#ifdef QT_GUI_LIB
  virtual bool createTreeWidgetItems(VTreeWidgetItem* parent, VObject* object, QMetaProperty mpro);
#endif // QT_GUI_LIB
};

class VObjectListSerializer : public VSerializer
{
public:
  virtual bool load(VObject* object, QMetaProperty mpro, VRep& rep);
  virtual bool save(VObject* object, QMetaProperty mpro, VRep& rep);
#ifdef QT_GUI_LIB
  virtual bool createTreeWidgetItems(VTreeWidgetItem* parent, VObject* object, QMetaProperty mpro);
#endif // QT_GUI_LIB
};

class VSerializerMgr
{
protected:
  QList<VSerializer*> serializerList;

public:
  virtual bool load(VObject* object, QMetaProperty mpro, VRep& rep);
  virtual bool save(VObject* object, QMetaProperty mpro, VRep& rep);
#ifdef QT_GUI_LIB
  virtual bool createTreeWidgetItems(VTreeWidgetItem* parent, VObject* object, QMetaProperty mpro);
#endif // QT_GUI_LIB

public:
  static void _initialize();
  static VSerializerMgr& instance();
};

#endif // VSERIALIZER_H
