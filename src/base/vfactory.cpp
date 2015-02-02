#include <stdio.h> // for fprintf
#include "vfactory.h"

VFactory::VFactory()
{
  createMap.clear();
  hierachyMap.clear();
  categoryMap.clear();
}

VFactory::~VFactory()
{
  createMap.clear();
  hierachyMap.clear();
  categoryMap.clear();
}

void VFactory::registerMetaObject(const QMetaObject* mobj)
{
  while (mobj != NULL)
  {
    QString className = QString(mobj->className());
    createMap[className] = mobj;

    const QMetaObject* parentMObj = mobj->superClass();
    VMetaObjectList& mobjList = hierachyMap[parentMObj];
    if (mobjList.indexOf(mobj) == -1)
      mobjList.push_back(mobj);

    mobj = parentMObj;
  }
}

void VFactory::registerMetaObjectByCategoryName(const QMetaObject* mobj, QString categoryName)
{
  if (QString(mobj->className()) == categoryName)
  {
    fprintf(stderr, "className is equal to categoryName (%s)\n", mobj->className());
    return;
  }
  registerMetaObject(mobj);
  VMetaObjectList& mobjList = categoryMap[categoryName];
  if (mobjList.indexOf(mobj) == -1)
    mobjList.push_back(mobj);
}

VFactory::VMetaObjectList VFactory::findMetaObjectsByParentClassName(QString parentClassName)
{
  for (VHierachyMap::iterator it = hierachyMap.begin(); it != hierachyMap.end(); it++)
  {
    const QMetaObject* mobj = it.key();
    if (mobj == NULL) continue;
    if (QString(mobj->className()) == parentClassName)
    {
      VMetaObjectList& mobjList = it.value();
      return mobjList;
    }
  }
  return VMetaObjectList();
}

VFactory::VMetaObjectList VFactory::findMetaObjectsByAncestorClassName(QString ancestorClassName)
{
  VMetaObjectList res;
  for (VHierachyMap::iterator it = hierachyMap.begin(); it != hierachyMap.end(); it++)
  {
    const QMetaObject* mobj = it.key();
    if (mobj == NULL) continue;
    if (isAncestor(mobj, ancestorClassName))
    {
      VMetaObjectList& mobjList = it.value();
      res += mobjList;
    }
  }
  return res;
}

VFactory::VMetaObjectList VFactory::findMetaObjectsByCategoryName(QString categoryName)
{
  for (VCategoryMap::iterator it = categoryMap.begin(); it != categoryMap.end(); it++)
  {
    QString _categoryName = it.key();
    if (_categoryName == categoryName)
    {
      VMetaObjectList& mobjList = it.value();
      return mobjList;
    }
  }
  return VMetaObjectList();
}

QObject* VFactory::createObjectByClassName(QString className)
{
  VCreateMap::iterator it = createMap.find(className);
  if (it == createMap.end())
    return NULL;
  const QMetaObject* mobj = it.value();
  if (mobj == NULL)
    return NULL;
  QObject* obj = mobj->newInstance();
  if (obj == NULL)
    return NULL;
  return obj;
}

#include <VObject>
#include <VXmlDoc>
QObject* VFactory::createObjectByDefaultDoc(const QString& path)
{
  VXmlDoc& doc = VXmlDoc::instance();
  VXml xml = doc.root().findChilds(path);
  if (xml.isNull()) return NULL;

  QString className = xml.getStr("_class", "");
  if (className == "")
  {
    return NULL;
  }
  VObject* obj = dynamic_cast<VObject*>(VFactory::instance().createObjectByClassName(className));
  if (obj == NULL)
  {
    return NULL;
  }
  obj->load(xml);
  return obj;
}

bool VFactory::isAncestor(const QMetaObject* mobj, QString className)
{
  while (mobj != NULL)
  {
    if (QString(mobj->className()) == className)
      return true;
    mobj = mobj->superClass();
  }
  return false;
}

VFactory& VFactory::instance()
{
  static VFactory factory;
  return factory;
}

#ifdef GTEST

class VFactoryTest : public testing::Test
{
protected:
  VFactory factory;
  virtual void SetUp()
  {
    Obj1 obj1;
    factory.registerMetaObject(obj1.metaObject());
    Obj2 obj2;
    factory.registerMetaObject(obj2.metaObject());
    Obj3 obj3;
    factory.registerMetaObject(obj3.metaObject());

    Obj31 obj31;
    factory.registerMetaObject(obj31.metaObject());
    Obj32 obj32;
    factory.registerMetaObject(obj32.metaObject());
    Obj33 obj33;
    factory.registerMetaObject(obj33.metaObject());
    Obj34 obj34;
    factory.registerMetaObject(obj34.metaObject());

    factory.registerMetaObjectByCategoryName(obj1.metaObject(), "MyObj");
    factory.registerMetaObjectByCategoryName(obj2.metaObject(), "MyObj");
    factory.registerMetaObjectByCategoryName(obj3.metaObject(), "MyObj");
  }

  virtual void TearDown()
  {

  }
};

TEST_F(VFactoryTest, createObjectTest)
{
  QObject* object;

  object = factory.createObjectByClassName("Obj");
  EXPECT_TRUE(dynamic_cast<Obj*>(object) != NULL);
  delete object;

  object = factory.createObjectByClassName("Obj1");
  EXPECT_TRUE(dynamic_cast<Obj1*>(object) != NULL);
  delete object;

  object = factory.createObjectByClassName("Obj2");
  EXPECT_TRUE(dynamic_cast<Obj2*>(object) != NULL);
  delete object;

  object = factory.createObjectByClassName("Obj3");
  EXPECT_TRUE(dynamic_cast<Obj3*>(object) != NULL);
  delete object;

  object = factory.createObjectByClassName("Obj31");
  EXPECT_TRUE(dynamic_cast<Obj31*>(object) != NULL);
  delete object;

  object = factory.createObjectByClassName("Obj32");
  EXPECT_TRUE(dynamic_cast<Obj32*>(object) != NULL);
  delete object;

  object = factory.createObjectByClassName("Obj33");
  EXPECT_TRUE(dynamic_cast<Obj33*>(object) != NULL);
  delete object;

  object = factory.createObjectByClassName("Obj34");
  EXPECT_TRUE(dynamic_cast<Obj34*>(object) != NULL);
  delete object;
}

TEST_F(VFactoryTest, parentClassNameTest)
{
  {
    VFactory::VMetaObjectList mobjList = factory.findMetaObjectsByParentClassName("Obj");
    foreach (const QMetaObject* mobj, mobjList)
    {
      printf("%s ", mobj->className());
    }
    printf("\n");
    EXPECT_EQ(mobjList.size(), 3); // Obj1, Obj2, Obj3
  }
  {
    VFactory::VMetaObjectList mobjList = factory.findMetaObjectsByParentClassName("Obj3");
    foreach (const QMetaObject* mobj, mobjList)
    {
      printf("%s ", mobj->className());
    }
    printf("\n");
    EXPECT_EQ(mobjList.size(), 4); // Obj31, Obj32, Obj33, Obj34
  }
}

TEST_F(VFactoryTest, ancestorClassNameTest)
{
  {
    VFactory::VMetaObjectList mobjList = factory.findMetaObjectsByAncestorClassName("Obj");
    foreach (const QMetaObject* mobj, mobjList)
    {
      printf("%s ", mobj->className());
    }
    printf("\n");
    EXPECT_EQ(mobjList.size(), 7); // Obj1, Obj2, Obj3, Obj31, Obj32, Obj33, Obj34
  }
  {
    VFactory::VMetaObjectList mobjList = factory.findMetaObjectsByParentClassName("Obj3");
    foreach (const QMetaObject* mobj, mobjList)
    {
      printf("%s ", mobj->className());
    }
    printf("\n");
    EXPECT_EQ(mobjList.size(), 4); // Obj31, Obj32, Obj33, Obj34
  }
}

#endif // GTEST
