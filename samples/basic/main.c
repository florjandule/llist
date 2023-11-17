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
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;
	printf("Hello World!\n");
	llist_set_heap_functions(malloc, free);
}