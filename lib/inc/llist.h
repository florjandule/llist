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

/**
 * @brief Function type for memory allocation
 *
 */
typedef void* (*llist_malloc_fn_t)(size_t size);

/**
 * @brief Function type for memory deallocation
 *
 */
typedef void (*llist_free_fn_t)(void* ptr);

/**
 * @brief Function type for comparing two data
 *
 * @details Returns 0 if the data is equal, otherwise returns a non-zero value
 *
 */
typedef int (*llist_compare_fn_t)(const void* a, const void* b);

/**
 * @brief Opaque Linked List Node Structure
 *
 */
typedef struct llist_node_s llist_node_t;

/**
 * @brief Opaque Linked List Structure
 *
 */
typedef struct llist_s llist_t;

/************************************
 * EXPORTED VARIABLES
 ************************************/

/************************************
 * GLOBAL FUNCTION PROTOTYPES
 ************************************/

/**
 * @brief Sets the memory management functions
 *
 * @param [in] malloc_fn Pointer to the memory allocation function
 * @param [in] free_fn Pointer to the memory deallocation function
 * @return int \c 0 if successful, otherwise \c -1
 */
int llist_set_memory_management_functions(llist_malloc_fn_t malloc_fn, llist_free_fn_t free_fn);

/**
 * @brief Create a linked list object
 *
 * @param [in] free_fn Pointer to the free data function (optional).
 * If set data will be freed when the removed from the list.
 * If \c NULL the data will not be freed, so, the user is responsible for freeing the data.
 * @return llist_t* Pointer to the linked list object if successful, otherwise \c NULL
 */
llist_t* llist_create(llist_free_fn_t free_fn);

/**
 * @brief Destroy the linked list object
 *
 * @details Removes all the data from the list
 * @details If the free data function is set, it will be called for each data
 *
 * @param [in] list Pointer to the linked list object
 * @return int \c 0 if successful, otherwise \c -1
 */
int llist_destroy(llist_t* list);

/**
 * @brief Pushes data to the front of the list
 *
 * @param [in] list Pointer to the linked list object
 * @param [in] data Pointer to the data
 * @return int \c 0 if successful, otherwise \c -1
 */
int llist_push_front(llist_t* list, void* data);

/**
 * @brief Pushes data to the back of the list
 *
 * @param [in] list Pointer to the linked list object
 * @param [in] data Pointer to the data
 * @return int \c 0 if successful, otherwise \c -1
 */
int llist_push_back(llist_t* list, void* data);

/**
 * @brief Insert data before a node
 *
 * @param [in] list Pointer to the linked list object
 * @param [in] reference_node Pointer to the reference node
 * @param [in] data Pointer to the data
 * @return int \c 0 if successful, otherwise \c -1
 */
int llist_insert_before(llist_t* list, const llist_node_t* reference_node, void* data);

/**
 * @brief Insert data after a node
 *
 * @param [in] list Pointer to the linked list object
 * @param [in] reference_node Pointer to the reference node
 * @param [in] data Pointer to the data
 * @return int \c 0 if successful, otherwise \c -1
 */
int llist_insert_after(llist_t* list, llist_node_t* reference_node, void* data);

/**
 * @brief Remove a node from the list
 *
 * @details If the free data function is set, it will be called for the node
 *
 * @param [in] list Pointer to the linked list object
 * @param [in] node Pointer to the node
 * @return int \c 0 if successful, otherwise \c -1
 */
int llist_remove(llist_t* list, llist_node_t* node);

/**
 * @brief Removes the data from the front of the list
 *
 * @details If the free data function is set, it will be called to free the data
 *
 * @param [in] list Pointer to the linked list object
 * @return int \c 0 if successful, otherwise \c -1
 */
int llist_remove_first(llist_t* list);

/**
 * @brief Removes the data from the back of the list
 *
 * @details If the free data function is set, it will be called for the data
 *
 * @param [in] list Pointer to the linked list object
 * @return int \c 0 if successful, otherwise \c -1
 */
int llist_remove_last(llist_t* list);

/**
 * @brief Returns the size of the list
 *
 * @param [in] list Pointer to the linked list object
 * @return size_t Size of the list if successful, otherwise \c 0
 */
size_t llist_size(const llist_t* list);

/**
 * @brief Removes all the datas from the list
 *
 * @details If the free data function is set, it will be called for each data
 *
 * @param [in] list Pointer to the linked list object
 * @return int \c 0 if successful, otherwise \c -1
 */
int llist_clear(llist_t* list);

/**
 * @brief Checks if the list is empty
 *
 * @param [in] list Pointer to the linked list object
 * @return int \c 1 if the list is empty, otherwise \c 0
 */
int llist_is_empty(const llist_t* list);

/**
 * @brief Get the first node of the list
 *
 * @param [in] list Pointer to the linked list object
 * @return llist_node_t* Pointer to the first node of the list if successful, otherwise \c NULL
 */
llist_node_t* llist_get_first(const llist_t* list);

/**
 * @brief Get the last node of the list
 *
 * @param [in] list Pointer to the linked list object
 * @return llist_node_t* Pointer to the last node of the list if successful, otherwise \c NULL
 */
llist_node_t* llist_get_last(const llist_t* list);

/**
 * @brief Get the next node of the list
 *
 * @param [in] node Pointer to the node
 * @return llist_node_t* Pointer to the next node if successful, otherwise \c NULL
 */
llist_node_t* llist_get_next(const llist_node_t* node);

/**
 * @brief Find a node in the list
 *
 * @param [in] list Pointer to the linked list object
 * @param [in] compare_fn Pointer to the compare function. See \c #llist_compare_fn_t
 * @param [in] data Pointer to the data
 * @return llist_node_t* Pointer to the node if successful, otherwise \c NULL
 */
llist_node_t* llist_find(llist_t* list, llist_compare_fn_t compare_fn, const void* data);

/**
 * @brief Get the node value
 *
 * @param [in] node Pointer to the node
 * @return void* Pointer to the data if successful, otherwise \c NULL
 */
void* llist_get_value(const llist_node_t* node);

/**
 * @brief Get the value at the specified index
 *
 * @param [in] list Pointer to the linked list object
 * @param [in] index Index of the value
 * @return void* Pointer to the data if successful, otherwise \c NULL
 */
void* llist_get_value_at(llist_t* list, size_t index);

#ifdef __cplusplus
}
#endif

#endif // _LLIST_H_
