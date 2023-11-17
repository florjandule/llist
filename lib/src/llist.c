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
