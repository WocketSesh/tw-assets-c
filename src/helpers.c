#include "helpers.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

ErrorValue array_init(BaseArray *base, size_t size) {
  base->length = 0;
  base->allocated_length = 0;
  base->size = size;

  base->contents = malloc(size * 2);

  if (base->contents == NULL) {
    return (struct ErrorValue){1, "Error Allocating Memory"};
  }

  return (struct ErrorValue){0};
}

ErrorValue array_allocate(BaseArray *base) {
  int new_allocated_length =
      base->allocated_length == 0 ? 2 : base->allocated_length * 2;

  void **tmp = realloc(base->contents, base->size * new_allocated_length);
  if (tmp == NULL) {
    return (ErrorValue){1, "Error Reallocating Memory"};
  }

  base->contents = tmp;

  base->allocated_length = new_allocated_length;
  return (struct ErrorValue){0};
}

ErrorValue array_push(BaseArray *base, void *content) {
  if (content == NULL) {
    return (ErrorValue){1, "Attempting to push NULL to array"};
  }

  ErrorValue err = array_needs_allocation(base) ? array_allocate(base)
                                                : (struct ErrorValue){0};

  if (err.did_error)
    return err;

  base->contents[base->length] = content;
  base->length++;

  return (ErrorValue){0};
}

int array_needs_allocation(struct BaseArray *base) {
  return (base->length + 1 > base->allocated_length);
}

void *array_get(BaseArray *base, int index, ErrorValue *err) {

  if (index >= base->length) {
    if (err != NULL) {
      err->did_error = 1;
      err->error_message = "Attempt to out of bounds index";
    }
    return NULL;
  }

  void *at_index = base->contents[index];

  if (at_index == NULL) {
    if (err != NULL) {
      err->did_error = 1;
      err->error_message = "Value at index is NULL";
    }
    return NULL;
  }

  if (err != NULL)
    err->did_error = 0;

  return at_index;
}

ErrorValue array_remove(BaseArray *base, int index, int free_memory) {

  ErrorValue err;

  if (free_memory) {
    free(array_get(base, index, &err));
  }
  for (int i = index; i + 1 < base->length; i++) {
    base->contents[i] = base->contents[i + 1];
  }

  base->contents[base->length] = NULL;
  base->length--;

  return (ErrorValue){0};
}

ErrorValue array_clear(BaseArray *base) {
  while (base->length > 0) {
    array_remove(base, 0, 1);
  }

  return (ErrorValue){0};
}
