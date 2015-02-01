// ----------------------------------------------------------------------------
//
// VDream Component Suite version 9.01
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __V_LIST_WIDGET_H__
#define __V_LIST_WIDGET_H__

#ifdef QT_GUI_LIB

#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <VLog>
#include <VObject>

// ----------------------------------------------------------------------------
// VListWidgetAccessible
// ----------------------------------------------------------------------------
class VListWidgetAccessible
{
public:
  virtual void  widgetClear()                                                             = 0;
  virtual int   widgetCount()                                                             = 0;
  virtual void* widgetAt(int i)                                                           = 0;
  virtual void  widgetPushBack(void* item)                                                = 0;
  virtual void* widgetCeateItem()                                                         = 0;
  virtual void  widgetItemIntoTreeWidgetItem(void* item, QTreeWidgetItem* treeWidgetItem) = 0;
  virtual void  widgetTreeWidgetItemIntoItem(QTreeWidgetItem* treeWidgetItem, void* item) = 0;
};

// ----------------------------------------------------------------------------
// VListWidget
// ----------------------------------------------------------------------------
namespace Ui {
  class VListWidget;
}

class VListWidget : public QWidget
{
  Q_OBJECT

protected:
  VListWidgetAccessible* accessible;

public:
  explicit VListWidget(QWidget *parent, VListWidgetAccessible* accessible);
  ~VListWidget();

public:
  void itemsIntoTreeWidget();
  void treeWidgetIntoItems();

protected slots:
  void __on_pbAdd_clicked();
  void __on_pbDel_clicked();

public:
  Ui::VListWidget *ui;
};
#else // QT_GUI_LIB
class VListWidgetAccessible {};
#endif // QT_GUI_LIB

#endif // __V_LIST_WIDGET_H__
