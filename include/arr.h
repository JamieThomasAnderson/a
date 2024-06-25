/*
* Dynamic Array
*/

#ifndef ARR_H
#define ARR_H

#include <stddef.h>

typedef struct {
  void *array;
  size_t used;
  size_t count;
  size_t size;
} Array;

void init_array(Array *a, size_t length, size_t size);
void insert_array(Array *a, void *item);
void free_array(Array *a);

#endif