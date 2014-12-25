#ifdef GTEST
#include <VDebugNewCancel>
#include <gtest/gtest.h>
#include <VInt>
#include <VInstance>

TEST( Design, instanceTest )
{
	{
		VInt& myInt = VInstance<VInt>::instance();
		int first = myInt; // 0
		EXPECT_TRUE( first == 0 );
		myInt = 1;
	 }

	{
		VInt& myInt = VInstance<VInt>::instance();
		int second = myInt; // 1
		EXPECT_TRUE( second == 1 );
	}
}

#endif // GTEST
