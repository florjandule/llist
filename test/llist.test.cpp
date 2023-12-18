#include <gtest/gtest.h>

#include "llist.c"

static void* test_malloc(size_t size)
{
	return malloc(size);
}

static void test_free(void* ptr)
{
	free(ptr);
}
class LlistTestF : public ::testing::Test
{
protected:
	void SetUp() override
	{
		llist_set_memory_management_functions(test_malloc, test_free);
	}

	void TearDown() override
	{
		/**/
	}
};

TEST(LlistTest, llist_set_memory_management_functions_nullptr)
{
	EXPECT_NE(llist_set_memory_management_functions(nullptr, nullptr), 0);
	EXPECT_NE(llist_set_memory_management_functions(test_malloc, nullptr), 0);
	EXPECT_NE(heap_malloc, test_malloc);
	EXPECT_NE(llist_set_memory_management_functions(nullptr, test_free), 0);
	EXPECT_NE(heap_free, test_free);
}

TEST(LlistTest, llist_set_memory_management_functions_valid)
{
	EXPECT_EQ(llist_set_memory_management_functions(test_malloc, test_free), 0);
	EXPECT_EQ(heap_malloc, test_malloc);
	EXPECT_EQ(heap_free, test_free);
}
