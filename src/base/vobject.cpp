#include <VLog>
#include <VObject>
#include <VDebugNew>

// ----------------------------------------------------------------------------
// VObjectConnection
// ----------------------------------------------------------------------------
VObjectConnection::VObjectConnection(QByteArray signal, QObject* receiver, QByteArray slot)
{
  this->signal   = signal;
  this->receiver = receiver;
  this->slot     = slot;
}

VObjectConnection::VObjectConnection(const char* signal, QObject* receiver, const char* slot)
{
  this->signal   = signal;
  this->receiver = receiver;
  this->slot     = slot;
}

bool VObjectConnection::operator == (const VObjectConnection& r) const
{
  if (this->signal != r.signal)     return false;
  if (this->receiver != r.receiver) return false;
  if (this->slot != r.slot)         return false;
  return true;
}

// ----------------------------------------------------------------------------
// VObject
// ----------------------------------------------------------------------------
VObject::VObject(void* owner) : QObject((QObject*)owner) // gilgil temp 2012.05.29
{
  this->owner = owner;
  tag = 0;
  error.clear();
}

VObject::~VObject()
{

}

bool VObject::connect(QObject* sender, const char* signal, QObject* receiver, const char* slot, Qt::ConnectionType type)
{
  //LOG_DEBUG("%s %s > %s %s %d", sender->metaObject()->className(), signal, receiver->metaObject()->className(), slot, (int)type); // gilgil temp 2014.03.10
  bool res = QObject::connect(sender, signal, receiver, slot, type);
  if (!res)
  {
    LOG_ERROR("VObject::connect(%s %s > %s %s %d) return false", sender->metaObject()->className(), signal, receiver->metaObject()->className(), slot, (int)type);
    return false;
  }
  VObject* vsender = dynamic_cast<VObject*>(sender);
  if (vsender != NULL)
  {
    VObjectConnection connection(signal, receiver, slot);
    vsender->connections.push_back(connection);
  }
  return res;
}

bool VObject::connect(QObject *sender, const QMetaMethod &signal, QObject *receiver, const QMetaMethod &slot, Qt::ConnectionType type)
{
  QByteArray baSignal = signal.methodSignature();
  baSignal = "2" + baSignal; // # define SIGNAL(a)   qFlagLocation("2"#a QLOCATION)
  QByteArray baSlot  = slot.methodSignature();
  baSlot = "1" + baSlot;    // # define SLOT(a)     qFlagLocation("1"#a QLOCATION)
  return VObject::connect(sender, baSignal.data(), receiver, baSlot.data(), type);
}

bool VObject::disconnect(QObject* sender, const char* signal, QObject* receiver, const char* slot)
{
  //LOG_DEBUG("%s %s > %s %s", sender->metaObject()->className(), signal, receiver->metaObject()->className(), slot); // gilgil temp 2014.03.10
  bool res = QObject::disconnect(sender, signal, receiver, slot);
  if (!res)
  {
    LOG_ERROR("VObject::disconnect(%s %s > %s %s) return false", sender->metaObject()->className(), signal, receiver->metaObject()->className(), slot);
    return false;
  }
  VObject* vsender = dynamic_cast<VObject*>(sender);
  if (vsender != NULL)
  {
    VObjectConnection connection(signal, receiver, slot);
    int index = vsender->connections.indexOf(connection);
    if (index != -1)
      vsender->connections.removeAt(index);
  }
  return res;
}

bool VObject::disconnect(QObject *sender, const QMetaMethod &signal, QObject *receiver, const QMetaMethod &slot)
{
  QByteArray baSignal = signal.methodSignature();
  baSignal = "2" + baSignal; // # define SIGNAL(a)   qFlagLocation("2"#a QLOCATION)
  QByteArray baSlot  = slot.methodSignature();
  baSlot = "1" + baSlot;     // # define SLOT(a)     qFlagLocation("1"#a QLOCATION)
  return VObject::disconnect(sender, baSignal.data(), receiver, baSlot.data());
}

QMetaMethod VObject::findMethod(QObject* object, QString methodName)
{
  if (object == NULL)
  {
    LOG_ERROR("object is null for method('%s')", qPrintable(methodName));
    QMetaMethod blankMethod;
    return blankMethod;
  }
  int _count = object->metaObject()->methodCount();
  for (int i = 0; i < _count; i++)
  {
    QMetaMethod res = object->metaObject()->method(i);
    QString signature = QString(res.methodSignature());
    if (signature == methodName)
    {
      return res;
    }
  }
  LOG_ERROR("can not find method('%s')", qPrintable(methodName));
  QMetaMethod blankMethod;
  return blankMethod;
}

void VObject::load(VXml xml)
{
  Q_UNUSED(xml) // gilgil temp 2015.01.29
}

void VObject::save(VXml xml)
{
  xml.setStr("_class", className());
}
