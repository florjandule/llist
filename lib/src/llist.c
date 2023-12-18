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

/**
 * @brief Linked List Node Structure
 *
 */
struct llist_node_s
{
	void* data; ///< Pointer to the data
	struct llist_node_s* next; ///< Pointer to the next node
};

/**
 * @brief Linked List Structure
 *
 */
struct llist_s
{
	llist_node_t* head; ///< Pointer to the head node
	llist_node_t* tail; ///< Pointer to the tail node
	size_t size; ///< Size of the list
	llist_free_fn_t free_fn; ///< Pointer to the free data function
};

/************************************
 * PRIVATE TYPEDEFS
 ************************************/

/************************************
 * STATIC VARIABLES
 ************************************/
static llist_malloc_fn_t heap_malloc = malloc;
static llist_free_fn_t heap_free = free;

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

int llist_set_memory_management_functions(llist_malloc_fn_t malloc_fn, llist_free_fn_t free_fn)
{
	if (malloc_fn == NULL || free_fn == NULL)
	{
		return -1;
	}

	heap_malloc = malloc_fn;
	heap_free = free_fn;

	return 0;
}

llist_t* llist_create(llist_free_fn_t free_fn)
{
	llist_t* list = (llist_t*)heap_malloc(sizeof(llist_t));
	if (NULL == list)
	{
		return NULL;
	}

	memset(list, 0, sizeof(llist_t));

	list->free_fn = free_fn;

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
	llist_node_t* node = (llist_node_t*)heap_malloc(sizeof(llist_node_t));
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

	llist_node_t* node = (llist_node_t*)heap_malloc(sizeof(llist_node_t));
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

int llist_insert_before(llist_t* list, const llist_node_t* reference_node, void* data)
{
	if (NULL == list)
	{
		return -1;
	}

	if (reference_node == list->head)
	{
		return llist_push_front(list, data);
	}

	llist_node_t* new_node = (llist_node_t*)heap_malloc(sizeof(llist_node_t));
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

int llist_insert_after(llist_t* list, llist_node_t* reference_node, void* data)
{
	if (NULL == list)
	{
		return -1;
	}

	llist_node_t* new_node = (llist_node_t*)heap_malloc(sizeof(llist_node_t));
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

int llist_remove(llist_t* list, llist_node_t* node)
{
	if (NULL == list)
	{
		return -1;
	}

	if (list->head == node)
	{
		return llist_remove_first(list);
	}
	if (list->tail == node)
	{
		return llist_remove_last(list);
	}
	llist_node_t* current = list->head;
	while (current && current->next != node)
	{
		current = current->next;
	}
	if (!current)
	{
		return -1;
	}
	current->next = node->next;
	if (list->free_fn)
	{
		list->free_fn(node->data);
	}
	heap_free(node);
	list->size--;
	return 0;
}

int llist_remove_first(llist_t* list)
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
	if (list->free_fn)
	{
		list->free_fn(node->data);
	}
	heap_free(node);
	list->size--;
	return 0;
}

int llist_remove_last(llist_t* list)
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

	if (list->free_fn)
	{
		list->free_fn(node->data);
	}
	heap_free(node);
	list->size--;
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

int llist_clear(llist_t* list)
{
	if (NULL == list)
	{
		return -1;
	}

	llist_node_t* current = list->head;
	while (current)
	{
		llist_node_t* next = current->next;
		if (list->free_fn)
		{
			list->free_fn(current->data);
		}
		heap_free(current);
		current = next;
	}
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return 0;
}

int llist_is_empty(const llist_t* list)
{
	return llist_size(list) == 0;
}

llist_node_t* llist_get_first(const llist_t* list)
{
	if (NULL == list)
	{
		return NULL;
	}

	return list->head;
}

llist_node_t* llist_get_last(const llist_t* list)
{
	if (NULL == list)
	{
		return NULL;
	}

	return list->tail;
}

llist_node_t* llist_get_next(const llist_node_t* node)
{
	if (NULL == node)
	{
		return NULL;
	}

	return node->next;
}

llist_node_t* llist_find(llist_t* list, llist_compare_fn_t compare_fn, const void* data)
{
	if (NULL == list || NULL == compare_fn)
	{
		return NULL;
	}

	llist_node_t* current = list->head;
	while (current)
	{
		if (0 == compare_fn(current->data, data))
		{
			return current;
		}
		current = current->next;
	}
	return NULL;
}

void* llist_get_value(const llist_node_t* node)
{
	if (NULL == node)
	{
		return NULL;
	}

	return node->data;
}

void* llist_get_value_at(llist_t* list, size_t index)
{
	if (NULL == list)
	{
		return NULL;
	}

	if (index >= list->size)
	{
		return NULL;
	}
	llist_node_t* current = list->head;
	for (size_t i = 0; i < index; i++)
	{
		current = current->next;
	}
	return current->data;
}
