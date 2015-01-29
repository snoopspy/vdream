#include "vdatachange.h"

// ----------------------------------------------------------------------------
// VDataChangeItem
// ----------------------------------------------------------------------------
VDataChangeItem::VDataChangeItem()
{
  enabled  = true;
  log      = true;
  replace  = "";
}

int VDataChangeItem::change(QByteArray& ba, int offset)
{
  QString text = QString::fromLatin1(ba);

  VLock lock(*pCs);
  int index = rx.indexIn(text, offset);
  if (index == -1) return -1;

  QString found = rx.cap(0);
  if (found == replace) return -1;
  text.replace(index, found.length(), replace);
  ba = text.toLatin1();

  if (log)
  {
    LOG_INFO("changed \"%s\" > \"%s\"", qPrintable(found), qPrintable(replace));
  }

  return index + replace.length();
}

// ----- gilgil temp 2015.01.29 ----- serialize
/*
void VDataChangeItem::load(VRep& rep)
{
  VRegExp::load(xml);

  enabled  = rep.getBool("enabled", enabled);
  log      = rep.getBool("log", log);
  replace  = rep.getArr("replace", replace);
}

void VDataChangeItem::save(VRep& rep)
{
  VRegExp::save(xml);

  rep.setBool("enabled", enabled);
  rep.setBool("log",     log);
  rep.setArr("replace",  replace);
}
*/
// ----------------------------------

#ifdef QT_GUI_LIB
void VDataChangeItem::initialize(QTreeWidget* treeWidget)
{
  VRegExp::initialize(treeWidget);

  QStringList headerLables;
  for (int i = 0; i < treeWidget->columnCount(); i++) headerLables << treeWidget->headerItem()->text(i);
  headerLables << "Enabled" << "Log" << "Replace";
  treeWidget->setHeaderLabels(headerLables);

  treeWidget->setColumnWidth(ENABLED_IDX, 30);
  treeWidget->setColumnWidth(LOG_IDX,     30);
  // treeWidget->setColumnWidth(REPLACE_IDX, 0);

  treeWidget->header()->setSectionResizeMode(ENABLED_IDX,   QHeaderView::Interactive);
  treeWidget->header()->setSectionResizeMode(LOG_IDX,       QHeaderView::Interactive);
  treeWidget->header()->setSectionResizeMode(REPLACE_IDX,   QHeaderView::Stretch);
}

void operator << (QTreeWidgetItem& treeWidgetItem, VDataChangeItem& item)
{
  treeWidgetItem << (VRegExp&)item;

  treeWidgetItem.setCheckState(VDataChangeItem::ENABLED_IDX, item.enabled ? Qt::Checked : Qt::Unchecked);
  treeWidgetItem.setCheckState(VDataChangeItem::LOG_IDX,     item.log ? Qt::Checked : Qt::Unchecked);
  treeWidgetItem.setText(VDataChangeItem::REPLACE_IDX, QString(item.replace));
}

void operator << (VDataChangeItem& item, QTreeWidgetItem& treeWidgetItem)
{
  (VRegExp&)item << treeWidgetItem;

  item.enabled  = treeWidgetItem.checkState(VDataChangeItem::ENABLED_IDX) == Qt::Checked;
  item.log      = treeWidgetItem.checkState(VDataChangeItem::LOG_IDX)     == Qt::Checked;
  item.replace  = qPrintable(treeWidgetItem.text(VDataChangeItem::REPLACE_IDX));

  VError error; item.prepare(error);
}
#endif // QT_GUI_LIB

// ----------------------------------------------------------------------------
// VDataChange
// ----------------------------------------------------------------------------
VDataChange::VDataChange()
{
}

VDataChange::~VDataChange()
{
}

bool VDataChange::prepare(VError& error)
{
  for (int i = 0; i < items.count(); i++)
  {
    VDataChangeItem* item = (VDataChangeItem*)items.at(i);
    if (!item->prepare(error)) return false;
  }
  return true;
}

bool VDataChange::change(QByteArray& ba)
{
  bool res = false;
  for (int i = 0; i < items.count(); i++)
  {
    VDataChangeItem* item = (VDataChangeItem*)items.at(i);
    if (!item->enabled) continue;
    int offset = 0;
    while (true)
    {
      offset = item->change(ba, offset);
      if (offset == -1) break;
      res = true;
    }
  }
  return res;
}

// ----- gilgil temp 2015.01.29 ----- serialize
/*
void VDataChange::load(VRep& rep)
{
  clear();
  {
    xml_foreach (childXml, rep.childs())
    {
      VDataChangeItem item;
      item.load(childXml);
      push_back(item);
    }
  }
}

void VDataChange::save(VRep& rep)
{
  rep.clearChild();
  for (VDataChange::iterator it = begin(); it != end(); it++)
  {
    VDataChangeItem& item = *it;
    VXml childXml = rep.addChild("item");
    item.save(childXml);
  }
}
*/
// ----------------------------------

#ifdef QT_GUI_LIB
#include "ui_vlistwidget.h"
void VDataChange::optionAddWidget(QLayout* layout)
{
  VListWidget* widget = new VListWidget(layout->parentWidget(), this);
  VDataChangeItem::initialize(widget->ui->treeWidget);
  widget->setObjectName("dataChangeWidget");
  widget->itemsIntoTreeWidget();
  layout->addWidget(widget);
}

void VDataChange::optionSaveDlg(QDialog* dialog)
{
  VListWidget* widget = dialog->findChild<VListWidget*>("dataChangeWidget");
  LOG_ASSERT(widget != NULL);
  widget->treeWidgetIntoItems();
}
#endif // QT_GUI_LIB
