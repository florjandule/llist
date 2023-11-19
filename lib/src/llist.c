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

int llist_push_back(llist_t* list, void* data)
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
	node->next = NULL;
	if (list->tail)
	{
		list->tail->next = node;
	}
	list->tail = node;
	if (!list->head)
	{
		list->head = node;
	}
	list->size++;
	return 0;
}

int llist_pop_front(llist_t* list)
{
	if (NULL == list)
	{
		return -1;
	}

	if (!list->head)
	{
		return -1;
	}
	llist_node_t* node = list->head;
	list->head = node->next;
	if (list->tail == node)
	{
		list->tail = NULL;
	}
	heap_free(node);
	list->size--;
	return 0;
}

int llist_pop_back(llist_t* list)
{
	if (NULL == list)
	{
		return -1;
	}

	if (!list->tail)
	{
		return -1;
	}
	llist_node_t* node = list->tail;
	if (list->head == list->tail)
	{
		list->head = NULL;
		list->tail = NULL;
	}
	else
	{
		llist_node_t* current = list->head;
		while (current->next != list->tail)
		{
			current = current->next;
		}
		current->next = NULL;
		list->tail = current;
	}
	heap_free(node);
	list->size--;
	return 0;
}

int llist_prepend_node(llist_t* list, const llist_node_t* reference_node, void* data)
{
	if (NULL == list)
	{
		return -1;
	}

	if (reference_node == list->head)
	{
		return llist_push_front(list, data);
	}

	llist_node_t* new_node = heap_malloc(sizeof(llist_node_t));
	if (!new_node)
	{
		return -1;
	}
	new_node->data = data;

	llist_node_t* current = list->head;
	while (current && current->next != reference_node)
	{
		current = current->next;
	}

	if (!current)
	{
		heap_free(new_node);
		return -1;
	}

	new_node->next = current->next;
	current->next = new_node;
	list->size++;

	return 0;
}

int llist_append_node(llist_t* list, llist_node_t* reference_node, void* data)
{
	if (NULL == list)
	{
		return -1;
	}

	llist_node_t* new_node = heap_malloc(sizeof(llist_node_t));
	if (!new_node)
	{
		return -1;
	}
	new_node->data = data;
	new_node->next = reference_node->next;
	reference_node->next = new_node;
	if (list->tail == reference_node)
	{
		list->tail = new_node;
	}
	list->size++;

	return 0;
}

size_t llist_size(const llist_t* list)
{
	if (NULL == list)
	{
		return 0;
	}

	return list->size;
}

int llist_is_empty(const llist_t* list)
{
	return llist_size(list) == 0;
}

