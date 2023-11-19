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
	const llist_node_t* node = llist_get_first_node(list);
	printf("[");
	while (node != NULL)
	{
		printf("%s ", (char*)llist_get_node_value(node));
		node = llist_get_next_node(node);
	}
	printf("]\n");
}

int compare(const void* a, const void* b)
{
	return strcmp((const char*)a, (const char*)b);
}

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	llist_set_memory_management_functions(malloc, free);

	list = llist_create();

	for (uint8_t i = 0; i < sizeof(strings) / sizeof(strings[0]); i++)
	{
		llist_push_back(list, (void*)strings[i]);
	}

	llist_node_t* world_node = llist_find_node(list, compare, (void*)strings[1]);
	if (world_node != NULL)
	{
		printf("Found node with data: %s\n", (char*)world_node->data);
	}

	printf("List size: %zu\n", llist_size(list));

	printf("List before removing node:\n");

	print_list();

	llist_remove_node(list, world_node);

	printf("List after removing node:\n");

	print_list();
}
