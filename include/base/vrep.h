#ifndef VREP_H
#define VREP_H

#include <QVariantMap>

class VRep : public QVariantMap
{
public:
  VRep() {}
  VRep(const QVariantMap& rhs) { *((QVariantMap*)this) = rhs; }

public:
  QList<VRep> childs();
  void clearChilds();

public:
  bool loadFromFile(QString fileName);
  bool saveToFile(QString fileName);
  VRep* move(QString path, bool createNode);

public:
  static QString defaultFileName();
  static VRep& instance();
};
Q_DECLARE_METATYPE(VRep)

#endif // VREP_H
