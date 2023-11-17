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

typedef void* (*llist_malloc_fn)(size_t size);
typedef void (*llist_free_fn)(void*);

/************************************
 * EXPORTED VARIABLES
 ************************************/

/************************************
 * GLOBAL FUNCTION PROTOTYPES
 ************************************/

int llist_set_heap_functions(llist_malloc_fn malloc_fn, llist_free_fn free_fn);

#ifdef __cplusplus
}
#endif

#endif // _LLIST_H_