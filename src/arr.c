#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "arr.h"

void init_array(Array *a, size_t length, size_t size)
{
    a->array = malloc(length * size);
    a->used = 0;
    a->count = length;
    a->size = size;
}

void insert_array(Array *a, void *item)
{
    if ( a->used == a->count )
    {
        a->count *= 2;
        a->array = realloc(a->array, a->count * a->size);
    }
    memcpy((char*)a->array + a->used * a->size, item, a->size);
    a->used++;

}

void free_array(Array *a)
{
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}