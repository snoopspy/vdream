#ifdef GTEST
#include <VDebugNewCancel>
#include <gtest/gtest.h>
#include <VBase>

typedef VBase<int> MyInt;

TEST( Design, baseTest )
{
	MyInt a = 1;
	MyInt b = 2;
	MyInt c = a + b;
	EXPECT_EQ(c, 3);
}

TEST( Design, basePointerTest )
{
	MyInt a = 1;
	int *b = &a;
	a++;
	MyInt c = a + *b;
	EXPECT_TRUE(c == 4);
}

TEST( Design, baseConstPointerTest )
{
	MyInt a = 1;
	const int *b = &a;
	a++;
	MyInt c = a + *b;
	EXPECT_TRUE(c == 4);
}

TEST( Design, baseReferenceTest )
{
	MyInt a = 1;
	int& b = a;
	a++;
	MyInt c = a + b;
	EXPECT_TRUE(c == 4);
}

TEST( Design, baseConstReferenceTest )
{
	MyInt a = 1;
	const int& b = a;
	a++;
	MyInt c = a + b;
	EXPECT_TRUE(c == 4);
}

#endif // GTEST
