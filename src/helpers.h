#ifndef HELPERS_H
#define HELPERS_H

#include <stddef.h>

typedef struct BaseArray {
  int length;
  int allocated_length;
  size_t size;
  void **contents;
} BaseArray;

typedef struct ErrorValue {
  int did_error;
  const char *error_message;
} ErrorValue;

ErrorValue init_array(BaseArray *base, size_t size);
ErrorValue allocate_array(BaseArray *base);
ErrorValue push_array(BaseArray *base, void *content, size_t content_size);
void *get_array(BaseArray *base, int index, ErrorValue *err);
ErrorValue remove_array(BaseArray *base, int index, int free_memory);
ErrorValue clear_array(BaseArray *base);

int array_needs_allocation(BaseArray *base);

#endif
