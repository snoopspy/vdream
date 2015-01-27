#ifndef VREP_H
#define VREP_H

#include <QVariantMap>

class VRep : public QVariantMap
{
public:
  VRep() {}
  VRep(const QVariantMap& rhs) { *((QVariantMap*)this) = rhs; }

public:
  bool loadFromFile(QString fileName);
  bool saveToFile(QString fileName);
  VRep* move(QString path, bool createNode);

public:
  static QString defaultFileName();
  static VRep& instance();
};

#endif // VREP_H
