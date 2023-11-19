/**
 * @file llist.h
 * @author Florjan Dule (florjan.dule.eee@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-11-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef _LLIST_H_
#define _LLIST_H_

#ifdef __cplusplus
extern "C" {
#endif

/************************************
 * INCLUDES
 ************************************/

#include <stddef.h>

/************************************
 * MACROS AND DEFINES
 ************************************/

/************************************
 * TYPEDEFS
 ************************************/

typedef struct llist_node_t
{
	void* data;
	struct llist_node_t* next;
} llist_node_t;

typedef struct llist_t
{
	llist_node_t* head;
	llist_node_t* tail;
	size_t size;
} llist_t;

typedef void* (*llist_malloc_fn_t)(size_t size);
typedef void (*llist_free_fn_t)(void* ptr);

typedef int (*llist_compare_fn_t)(const void*, const void*);

/************************************
 * EXPORTED VARIABLES
 ************************************/

/************************************
 * GLOBAL FUNCTION PROTOTYPES
 ************************************/

int llist_set_memory_management_functions(llist_malloc_fn_t malloc_fn, llist_free_fn_t free_fn);

llist_t* llist_create(void);

int llist_destroy(llist_t* list);

int llist_push_front(llist_t* list, void* data);

int llist_push_back(llist_t* list, void* data);

int llist_pop_front(llist_t* list);

int llist_pop_back(llist_t* list);

int llist_insert_before_node(llist_t* list, const llist_node_t* reference_node, void* data);

int llist_insert_after_node(llist_t* list, llist_node_t* reference_node, void* data);

size_t llist_size(const llist_t* list);

int llist_is_empty(const llist_t* list);

void* llist_get_node_value(const llist_node_t* node);

void* llist_get_value_at(llist_t* list, size_t index);

int llist_remove_node(llist_t* list, llist_node_t* node);

int llist_clear(llist_t* list);

llist_node_t* llist_find_node(llist_t* list, llist_compare_fn_t compare_fn, const void* data);

llist_node_t* llist_get_first_node(const llist_t* list);

llist_node_t* llist_get_last_node(const llist_t* list);

#ifdef __cplusplus
}
#endif

#endif // _LLIST_H_
