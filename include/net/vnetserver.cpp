#include <VNetServer>

// ----------------------------------------------------------------------------
// VNetServer
// ----------------------------------------------------------------------------
VNetServer::VNetServer(void* owner) : VNet(owner)
{
  onceWriteSize = 0;
  port          = 0;
  localHost     = "";
}

VNetServer::~VNetServer()
{
}

void VNetServer::load(VXml &xml)
{
  VNet::load(xml);

  onceWriteSize = rep.getInt("onceWriteSize", onceWriteSize);
  port          = rep.getInt("port", port);
  localHost     = rep.getStr("localHost", localHost);
}

void VNetServer::save(VXml &xml)
{
  VNet::save(xml);

  rep.setInt("onceWriteSize", onceWriteSize);
  rep.setInt("port", port);
  rep.setStr("localHost", localHost);
}

#ifdef QT_GUI_LIB
void VNetServer::optionAddWidget(QLayout* layout)
{
  VOptionable::addLineEdit(layout, "leOnceWriteSize", "Once Write Size", QString::number(onceWriteSize));
  VOptionable::addLineEdit(layout, "lePort",      "Port",       QString::number(port));
  VOptionable::addLineEdit(layout, "leLocalHost", "Local Host", localHost);
}

void VNetServer::optionSaveDlg(QDialog* dialog)
{
  onceWriteSize = dialog->findChild<QLineEdit*>("leOnceWriteSize")->text().toInt();
  port          = dialog->findChild<QLineEdit*>("lePort")->text().toInt();
  localHost     = dialog->findChild<QLineEdit*>("leLocalHost")->text();
}
#endif // QT_GUI_LIB
