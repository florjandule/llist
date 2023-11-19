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

typedef void* (*llist_malloc_fn)(size_t size);
typedef void (*llist_free_fn)(void*);

/************************************
 * EXPORTED VARIABLES
 ************************************/

/************************************
 * GLOBAL FUNCTION PROTOTYPES
 ************************************/

int llist_set_heap_functions(llist_malloc_fn malloc_fn, llist_free_fn free_fn);

llist_t* llist_create(void);

int llist_destroy(llist_t* list);

int llist_push_front(llist_t* list, void* data);

int llist_push_back(llist_t* list, void* data);

#ifdef __cplusplus
}
#endif

#endif // _LLIST_H_