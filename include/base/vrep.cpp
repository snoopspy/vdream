#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include "vrep.h"

bool VRep::loadFromFile(QString fileName)
{
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly))
    return false;

  QByteArray ba = file.readAll();
  file.close();

  QJsonDocument jdoc = QJsonDocument::fromJson(ba);

  QJsonObject jobj = jdoc.object();

  *this = jobj.toVariantMap();

  return true;
}

bool VRep::saveToFile(QString fileName)
{
  QJsonObject jobj = QJsonObject::fromVariantMap(*this);

  QJsonDocument jdoc;
  jdoc.setObject(jobj);

  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly))
    return false;

  file.write(jdoc.toJson());
  file.close();

  return true;
}

VRep* VRep::move(QString path, bool createNode)
{
  VRep* res = this;
  QStringList nodes = path.split("/");
  foreach (QString node, nodes)
  {
    if (node == "") continue;
    VRep::iterator it = res->find(node);
    if (it == res->end())
    {
      if (!createNode) return NULL;
      res->insert(node, VRep());
      it = res->find(node);
    }
    QVariant& val = *it;
    res = (VRep*)(val.data());
  }
  return res;
}

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
QString VRep::defaultFileName()
{
  QString fileName         = QCoreApplication::applicationFilePath();
  QString path             = QFileInfo(fileName).path();
  QString completeBaseName = QFileInfo(fileName).completeBaseName();
  QString res              = path + QDir::separator() + completeBaseName + ".json";
  return res;
}

VRep& VRep::instance()
{
  static VRep rep;
  return rep;
}

#ifdef GTEST
#include <gtest/gtest.h>

TEST(RepTest, defaultFileNameTest)
{
  int argc = 1;
  QCoreApplication a(argc, NULL);
  QString fileName = VRep::defaultFileName();
  printf("QRep::defaultFileName() return %s\n", qPrintable(fileName));
}

#endif // GTEST
