/**
 * @file llist.c
 * @author Florjan Dule (florjan.dule.eee@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-11-17
 *
 * @copyright Copyright (c) 2023
 *
 */

/************************************
 * INCLUDES
 ************************************/

#include "llist.h"

#include <stdlib.h>
#include <string.h>

/************************************
 * EXTERN VARIABLES
 ************************************/

/************************************
 * PRIVATE MACROS AND DEFINES
 ************************************/

/************************************
 * PRIVATE TYPEDEFS
 ************************************/

/************************************
 * STATIC VARIABLES
 ************************************/
static llist_malloc_fn heap_malloc = malloc;
static llist_free_fn heap_free = free;

/************************************
 * GLOBAL VARIABLES
 ************************************/

/************************************
 * STATIC FUNCTION PROTOTYPES
 ************************************/

/************************************
 * STATIC FUNCTIONS
 ************************************/

/************************************
 * GLOBAL FUNCTIONS
 ************************************/

int llist_set_heap_functions(llist_malloc_fn malloc_fn, llist_free_fn free_fn)
{
	if (malloc_fn == NULL || free_fn == NULL)
	{
		return -1;
	}

	heap_malloc = malloc_fn;
	heap_free = free_fn;

	return 0;
}

llist_t* llist_create(void)
{
	llist_t* list = heap_malloc(sizeof(llist_t));
	if (NULL == list)
	{
		return NULL;
	}

	memset(list, 0, sizeof(llist_t));

	return list;
}

int llist_destroy(llist_t* list)
{
	if (NULL == list)
	{
		return -1;
	}

	llist_clear(list);

	heap_free(list);

	return 0;
}

int llist_push_front(llist_t* list, void* data)
{
	if (NULL == list)
	{
		return -1;
	}
	llist_node_t* node = heap_malloc(sizeof(llist_node_t));
	if (!node)
	{
		return -1;
	}
	node->data = data;
	node->next = list->head;
	list->head = node;
	if (!list->tail)
	{
		list->tail = node;
	}
	list->size++;
	return 0;
}
