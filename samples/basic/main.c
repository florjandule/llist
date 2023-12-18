/**
 * @file main.c
 * @author Florjan Dule (florjan.dule.eee@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-11-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "llist.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* const strings[] = {
	"Hello",
	"World",
	"!",
};

llist_t* list = NULL;

void print_list(void)
{
	if (list == NULL)
	{
		return;
	}
	const llist_node_t* node = llist_get_first(list);
	printf("[");
	while (node != NULL)
	{
		printf("%s ", (char*)llist_get_node(node));
		node = llist_get_next(node);
	}
	printf("]\n");
}

int compare(const void* a, const void* b)
{
	return strcmp((const char*)a, (const char*)b);
}

void free_data(void* data)
{
	printf("Freeing data: %s\n", (char*)data);
}

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	llist_set_memory_management_functions(malloc, free);

	list = llist_create(free_data);

	for (uint8_t i = 0; i < sizeof(strings) / sizeof(strings[0]); i++)
	{
		llist_push_back(list, (void*)strings[i]);
	}

	llist_node_t* world_node = llist_find(list, compare, (void*)strings[1]);
	if (world_node != NULL)
	{
		printf("Found node with data: %s\n", (char*)world_node->data);
	}

	printf("List size: %zu\n", llist_size(list));

	printf("List before removing node:\n");

	print_list();

	llist_remove(list, world_node);

	printf("List after removing node:\n");

	print_list();

	if (llist_destroy(list))
	{
		printf("Failed to destroy list\n");
	}
}
