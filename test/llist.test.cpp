#include <gtest/gtest.h>

#include "llist.c"

static const char* list_objects[] = {"first", "second", "third"};

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

TEST(LlistTest, llist_push_front_two_objects)
{
	int ret;
	llist_t* list = llist_create(NULL);
	ASSERT_NE(list, nullptr);

	// Add first and test
	ret = llist_push_front(list, (void*)list_objects[0]);
	ASSERT_EQ(0, ret);
	const char* first = (const char*)llist_get_value(llist_get_first(list));
	ASSERT_NE(first, nullptr);
	ASSERT_EQ(0, strcmp(first, "first"));

	// Add second to front and test
	ret = llist_push_front(list, (void*)list_objects[1]);
	first = (const char*)llist_get_value(llist_get_first(list));
	ASSERT_EQ(0, ret);
	ASSERT_NE(first, nullptr);
	ASSERT_EQ(0, strcmp(first, "second"));

	ret = llist_destroy(list);
	ASSERT_EQ(0, ret);
}
