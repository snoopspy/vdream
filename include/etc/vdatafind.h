// ----------------------------------------------------------------------------
//
// VDream Component Suite version 9.0
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __V_DATA_FIND_H__
#define __V_DATA_FIND_H__

#include <VObjectWidget>
#include <QRegExp>
#include <VListWidget>
#ifdef QT_GUI_LIB
#include <QTreeWidget>
#include <QHeaderView>
#endif // QT_GUI_LIB

// ----------------------------------------------------------------------------
// VRegExp
// ----------------------------------------------------------------------------
class VRegExp : public VObject
{
  Q_OBJECT
  Q_ENUMS(QRegExp::PatternSyntax) // gilgil temp 2015.01.29 serialize
  Q_ENUMS(Qt::CaseSensitivity) // gilgil temp 2015.01.29 serialize

  Q_PROPERTY(QString pattern MEMBER pattern)
  Q_PROPERTY(QRegExp::PatternSyntax syntax MEMBER syntax)
  Q_PROPERTY(Qt::CaseSensitivity cs MEMBER cs)
  Q_PROPERTY(bool minimal MEMBER minimal)

public:
  VRegExp();
  VRegExp(const VRegExp& b);
  virtual ~VRegExp();

public:
  QString                pattern;
  QRegExp::PatternSyntax syntax;
  Qt::CaseSensitivity    cs;
  bool                   minimal;

public:
  VCS*    pCs;
  QRegExp rx;
  bool prepare(VError& error);

  // ----- gilgil temp 2015.01.29 ----- serialize
  /*
public:
  virtual void load(VRep& rep);
  virtual void save(VRep& rep);
  */
  // ----------------------------------

#ifdef QT_GUI_LIB
public:
  static const int PATTERN_IDX   = 0;
  static const int SYNTAX_IDX    = 1;
  static const int CS_IDX        = 2;
  static const int MINIMAL_IDX   = 3;

  static void initialize(QTreeWidget* treeWidget);
#endif // QT_GUI_LIB
};
#ifdef QT_GUI_LIB
void operator << (QTreeWidgetItem& treeWidgetItem, VRegExp& regexp);
void operator << (VRegExp& regexp, QTreeWidgetItem& treeWidgetItem);
#endif // QT_GUI_LIB
Q_DECLARE_METATYPE(QRegExp::PatternSyntax)
Q_DECLARE_METATYPE(Qt::CaseSensitivity)

// ----------------------------------------------------------------------------
// VDataFindItem
// ----------------------------------------------------------------------------
class VDataFindItem : public VRegExp
{
  Q_OBJECT
  Q_PROPERTY(bool enabled MEMBER enabled)
  Q_PROPERTY(bool log MEMBER log)

public:
  VDataFindItem();

public:
  bool enabled;
  bool log;

public:
  int find(QByteArray& ba, int offset = 0);

  // ----- gilgil temp 2015.01.29 ----- serialize
  /*
public:
  virtual void load(VRep& rep);
  virtual void save(VRep& rep);
  */
  // ----------------------------------

#ifdef QT_GUI_LIB
public:
  static const int ENABLED_IDX = 4;
  static const int LOG_IDX     = 5;

  static void initialize(QTreeWidget* treeWidget);
#endif // QT_GUI_LIB
};

#ifdef QT_GUI_LIB
void operator << (QTreeWidgetItem& treeWidgetItem, VDataFindItem& item);
void operator << (VDataFindItem& item, QTreeWidgetItem& treeWidgetItem);
#endif // QT_GUI_LIB

// ----------------------------------------------------------------------------
// VDataFind
// ----------------------------------------------------------------------------
typedef _VObjectList<VDataFindItem> VDataFindItemList;
class VDataFind : public VObject, public VOptionable, public VListWidgetAccessible
{
  Q_OBJECT
  Q_PROPERTY(VObjectList* items READ getItems)

public:
  VDataFind();
  virtual ~VDataFind();

public:
  VDataFindItemList items;
  VObjectList* getItems() { return &items; }

public:
  bool prepare(VError& error);
  bool find(QByteArray& ba);

  // ----- gilgil temp 2015.01.29 ----- serialize
  /*
public:
  virtual void load(VRep& rep);
  virtual void save(VRep& rep);
  */
  // ----------------------------------

#ifdef QT_GUI_LIB
public: // VOptionable
  virtual void optionAddWidget(QLayout* layout);
  virtual void optionSaveDlg(QDialog* dialog);

public: // VListWidgetAccessible
  virtual void  widgetClear()                                                             { clear();                                  }
  virtual int   widgetCount()                                                             { return count();                           }
  virtual void* widgetAt(int i)                                                           { return  (void*)&at(i);                    }
  virtual void  widgetPushBack(void* item)                                                { push_back(*(const VDataFindItem*)item);   }
  virtual void* widgetCeateItem()                                                         { return new VDataFindItem;                 }
  virtual void  widgetItemIntoTreeWidgetItem(void* item, QTreeWidgetItem* treeWidgetItem) { *treeWidgetItem << *(VDataFindItem*)item; }
  virtual void  widgetTreeWidgetItemIntoItem(QTreeWidgetItem* treeWidgetItem, void* item) { *(VDataFindItem*)item << *treeWidgetItem; }
#endif // QT_GUI_LIB
};

#endif // __V_DATA_FIND_H__
