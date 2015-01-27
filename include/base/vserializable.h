#ifndef VSERIALIZABLE_H
#define VSERIALIZABLE_H

#include "vrep.h"

class VSerializable
{
public:
  virtual void load(VRep& rep) = 0;
  virtual void save(VRep& rep) = 0;

  bool loadFromFile(QString fileName, QString path = "");
  bool saveToFile(const QString fileName, QString path = "");
  bool loadFromDefaultDoc(QString path);
  bool saveToDefaultDoc(QString path);
};

#endif // VSERIALIZABLE_H
