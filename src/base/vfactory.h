#ifndef VFACTORY_H
#define VFACTORY_H

#include <QList>
#include <QMap>
#include <QMetaObject>
#include <QString>

class VFactory
{
public:
  typedef QList<const QMetaObject* /*mobj*/>                             VMetaObjectList;
  typedef QMap<QString             /*className*/,    const QMetaObject*> VCreateMap;
  typedef QMap<const QMetaObject*  /*parent mobj*/,  VMetaObjectList>    VHierachyMap;
  typedef QMap<QString,            /*category name*/ VMetaObjectList>    VCategoryMap;

  VCreateMap   createMap;
  VHierachyMap hierachyMap;
  VCategoryMap categoryMap;

public:
  VFactory();
  virtual ~VFactory();

  void registerMetaObject(const QMetaObject* mobj);
  void registerMetaObjectByCategoryName(const QMetaObject* mobj, QString categoryName);

  VMetaObjectList findMetaObjectsByParentClassName(QString parentClassName);
  VMetaObjectList findMetaObjectsByAncestorClassName(QString ancestorClassName);
  VMetaObjectList findMetaObjectsByCategoryName(QString categoryName);

  QObject* createObjectByClassName(QString className);
  static QObject* createObjectByDefaultDoc(const QString& path); // gilgil temp 2015.01.29 serialize

protected:
  static bool isAncestor(const QMetaObject* mobj, QString className);

public:
  static VFactory& instance();
};

#ifdef GTEST
#include <gtest/gtest.h>
#include <QObject>

/*
QObject
  +-Obj
    +-Obj1
    +-Obj2
    +-Obj3
      +-Obj31
      +-Obj32
      +-Obj33
      +-Obj34
*/

class Obj : public QObject
{
  Q_OBJECT
public:
  Q_INVOKABLE Obj() {}
};

class Obj1 : public Obj
{
  Q_OBJECT
public:
  Q_INVOKABLE Obj1() {}
};

class Obj2 : public Obj
{
  Q_OBJECT
public:
  Q_INVOKABLE Obj2() {}
};

class Obj3 : public Obj
{
  Q_OBJECT
public:
  Q_INVOKABLE Obj3() {}
};

class Obj31 : public Obj3
{
  Q_OBJECT
public:
  Q_INVOKABLE Obj31() {}
};

class Obj32 : public Obj3
{
  Q_OBJECT
public:
  Q_INVOKABLE Obj32() {}
};

class Obj33 : public Obj3
{
  Q_OBJECT
public:
  Q_INVOKABLE Obj33() {}
};

class Obj34 : public Obj3
{
  Q_OBJECT
public:
  Q_INVOKABLE Obj34() {}
};

#endif // GTEST

#endif // VFACTORY_H
