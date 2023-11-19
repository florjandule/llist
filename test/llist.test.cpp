#include <gtest/gtest.h>

#include "llist.c"

TEST(LlistText, llist_set_memory_management_functions)
{
	EXPECT_NE(llist_set_memory_management_functions(nullptr, nullptr), 0);
	EXPECT_NE(llist_set_memory_management_functions(malloc, nullptr), 0);
	EXPECT_NE(llist_set_memory_management_functions(nullptr, free), 0);
	EXPECT_EQ(llist_set_memory_management_functions(malloc, free), 0);
}
