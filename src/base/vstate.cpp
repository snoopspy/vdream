#include <VState>

// ----- gilgil temp 2015.02.03 -----
/*
// ----------------------------------------------------------------------------
// VState
// ----------------------------------------------------------------------------
VState::VState(const QString s)
{
  if (s == "None")         value = None;
  else if (s == "Closed")  value = Closed;
  else if (s == "Opening") value = Opening;
  else if (s == "Opened")  value = Opened;
  else if (s == "Closing") value = Closing;
  else value = None;
}

VState::operator QString() const
{
  QString res;
  switch (value)
  {
    case None:    res = "None";    break;
    case Closed:  res = "Closed";  break;
    case Opening: res = "Opening"; break;
    case Opened:  res = "Opened";  break;
    case Closing: res = "Closing"; break;
    default:      res = "None";    break;
  }
  return res;
}
*/
// ----------------------------------

#ifdef GTEST
#include <gtest/gtest.h>
#include <QDebug>

TEST(VStateTest, sizeTest)
{
  printf("sizeof(VState)=%zu\n", sizeof(VState));
  EXPECT_TRUE(sizeof(VState) == sizeof(int));
}

TEST(VStateTest, varTest)
{
  VState state = VState::Opened;
  QVariant var = QVariant::fromValue<VState>(state);

  int userType = var.userType();
  EXPECT_TRUE(userType == qMetaTypeId<VState>());

  QVariant::Type type = var.type();  // deprecated
  EXPECT_TRUE((int)type == QMetaType::User);

  QString typeName = var.typeName();
  EXPECT_TRUE(typeName == "VState");
}

#endif // GTEST
