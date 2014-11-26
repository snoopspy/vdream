#include <gtest/gtest.h>
#include <pthread.h>

void resolvePthreadLinkError()
{
	pthread_key_t key = -1;
	pthread_key_delete(key);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
