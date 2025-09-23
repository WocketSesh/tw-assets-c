#include "helpers.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct ErrorValue init_array(struct BaseArray *base, size_t size) {
  base->length = 0;
  base->allocated_length = 0;
  base->size = size;

  base->contents = malloc(size * 2);

  if (base->contents == NULL) {
    return (struct ErrorValue){1, "Error Allocating Memory"};
  }

  return (struct ErrorValue){0};
}

struct ErrorValue allocate_array(struct BaseArray *base) {
  int new_allocated_length =
      base->allocated_length == 0 ? 2 : base->allocated_length * 2;

  void **tmp = realloc(base->contents, base->size * new_allocated_length);
  if (tmp == NULL) {
    return (struct ErrorValue){1, "Error Reallocating Memory"};
  }

  base->contents = tmp;

  base->allocated_length = new_allocated_length;
  return (struct ErrorValue){0};
}

struct ErrorValue push_array(struct BaseArray *base, void *content,
                             size_t content_size) {
  if (content == NULL) {
    return (struct ErrorValue){1, "Attempting to push NULL to array"};
  }

  if (content_size != base->size) {
    return (struct ErrorValue){
        1, "Attempting to push content with mismatched size for array"};
  }

  struct ErrorValue err = array_needs_allocation(base) ? allocate_array(base)
                                                       : (struct ErrorValue){0};

  if (err.did_error)
    return err;

  base->contents[base->length] = content;
  base->length++;

  return (struct ErrorValue){0};
}

int array_needs_allocation(struct BaseArray *base) {
  return (base->length + 1 > base->allocated_length);
}

void *get_array(struct BaseArray *base, int index, ErrorValue *err) {

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

struct ErrorValue remove_array(struct BaseArray *base, int index,
                               int free_memory) {

  struct ErrorValue err;

  if (free_memory) {
    void *to_free = get_array(base, index, &err);

    if (to_free == NULL)
      return (struct ErrorValue){1,
                                 "[free_memory] Value at given index is NULL"};

    free(to_free);
  }
  for (int i = index; i + 1 < base->length; i++) {
    base->contents[i] = base->contents[i + 1];
  }

  base->contents[base->length] = NULL;
  base->length--;

  return (struct ErrorValue){0};
}

struct ErrorValue clear_array(struct BaseArray *base) {
  while (base->length > 0) {
    remove_array(base, 0, 1);
  }

  return (struct ErrorValue){0};
}
