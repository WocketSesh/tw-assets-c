#ifndef HELPERS_H
#define HELPERS_H

#include "tw_assets.h"
#include <stddef.h>

typedef struct BaseArray {
  int length;
  int allocated_length;
  size_t size;
  void **contents;
} BaseArray;

int array_length(BaseArray *base);
ErrorValue array_init(BaseArray *base, size_t size);
ErrorValue array_allocate(BaseArray *base);
ErrorValue array_push(BaseArray *base, void *content);
void *array_get(BaseArray *base, int index, ErrorValue *err);
ErrorValue array_remove(BaseArray *base, int index, int free_memory);
ErrorValue array_clear(BaseArray *base);
int array_needs_allocation(BaseArray *base);
void create_error(ErrorValue *err, const char *msg);

#endif
